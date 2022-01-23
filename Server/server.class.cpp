#include "server.class.h"

using std::cout; using std::endl; 
using std::string; using std::cerr;


Server::Server(int domain, int type, int protocol, const string& mailpool)
{
    _domain = domain;
    _type = type;
    _protocol = protocol;

    if((_sd = socket(_domain, _type, _protocol)) < 0)
        PrintErrorAndExitFail("Error while creating the server.");

    memset(&_myAddr, 0, sizeof(_myAddr));

    _ldap = new LDAPClass();
    _clientHandler = new ClientHandler();
}


Server::~Server()
{
    if(_clientHandler != nullptr)
        delete _clientHandler;
    
    if(_ldap != nullptr)
        delete _ldap;

    close(_sd);
}


string Server::ReadMessage(int socket)
{
    string message;

    int len = std::stoi(ReadLineSocket(socket)); // 4
    if(len == 0)
        return "quit";
    message = ReadNBytesSocket(socket, len + 1); // quit

    return message;
}


ClientConnected Server::AcceptClient()
{
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    socklen_t addrlen = sizeof(clientAddr);
    int socket = accept(_sd, (struct sockaddr*)&clientAddr, &addrlen);

    return ClientConnected(socket, inet_ntoa(clientAddr.sin_addr));
}


void Server::ClientThread(ClientConnected client)
{
    UserStruct userStruct;
    string request, command, response;
    
    if(!_clientHandler->ExistsInMap(client.GetIp()))
        _clientHandler->AddClient2Map(client.GetIp());

    while (true)
    {
        request = ReadMessage(client.GetSocket());
        command = boost::algorithm::to_lower_copy(ReadOneLine(request));
        cout << "Command: " << command << endl;

        // user wants to quit. No additional query is needed
        if(command == "quit")
        {
            std::cout << client.GetIp() << " is quitting." << std::endl;
            _clientHandler->DeleteClientFromMap(client.GetIp());
            break;
        }

        // check if logged in
        if(!client.LoggedIn() && command != "login")
        {
            SendMessage(client.GetSocket(), "You need to be logged in first.");
            continue;
        }

        // commands
        if(command == "login")
        {
            std::string username = ReadOneLine(request);
            std::string password = ReadOneLine(request);

            // ldap login
            if(!_ldap->LDAPLogin(username, password))
            {
                _clientHandler->AddFailedLoginAttempt(client.GetIp());
                
                if (_clientHandler->IsBlocked(client.GetIp())){
                    std::cout << "is blocked" << std::endl;
                    SendMessage(client.GetSocket(), "ERR\nYou're currently blocked. Try later");
                    break;
                }
                SendMessage(client.GetSocket(), "ERR");
                continue;
            }
            
            SendMessage(client.GetSocket(), "OK");
            userStruct.username = username;
            client.Login();
            continue;
        }
        else if(command == "send")
        {
            continue;
        }
        else if(command == "read")
        {
            continue;
        }
        else if(command == "list")
        {
            continue;
        }
        else if(command == "delete")
        {
            continue;
        }

        PrintErrorAndExitFail("Something went wrong.");
    }
    close(client.GetSocket());
}

bool Server::ClientIsBlocked(const std::string& ip){
    if(!_clientHandler->ExistsInMap(ip))
        return false;
    
    return _clientHandler->IsBlocked(ip);
}


void Server::StartServer(int backlog, const string& port)
{
    _myAddr.sin_family = _domain;
    _myAddr.sin_addr.s_addr = INADDR_ANY;

    try
    {
        _myAddr.sin_port = htons(std::stoi(port));
    }
    catch(...)
    {
        cerr << "Error converting port (htons)" << endl;
    }

    if((bind(_sd, (struct sockaddr*)&_myAddr, sizeof(_myAddr))) != 0)
        PrintErrorAndExitFail("Error while binding socket.");

    if(listen(_sd, backlog) == -1)
        PrintErrorAndExitFail("Error starting listening port");

    _listening = true;
    // establish message db
    // connect ldap
    _ldap->LDAPConnect();
}


void Server::SendMessage(int sd, const string& text)
{
    SendNBytesSocket(sd, std::to_string(text.size()).size() + 1, std::to_string(text.size()) + '\n');
    SendNBytesSocket(sd, text.size(), text);
}