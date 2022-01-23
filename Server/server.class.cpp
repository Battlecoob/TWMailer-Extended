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

    cout << "Client connected." << endl;
    return ClientConnected(socket, inet_ntoa(clientAddr.sin_addr));
}


void Server::ClientThread(ClientConnected client)
{
    UserStruct userStruct;
    string request, command, response;
    
    if(!_clientHandler->ExistsInMap(client.GetIp()))
        _clientHandler->AddClient2Map(client.GetIp());

    userStruct.username = "anonym";

    while (true)
    {
        request = ReadMessage(client.GetSocket());
        command = boost::algorithm::to_lower_copy(ReadOneLine(request));
        cout << "\nCommand: " << command << "\n" << endl;

        // user wants to quit. No additional query is needed
        if(command == "quit")
        {
            std::cout << userStruct.username << " is quitting." << std::endl;
            _clientHandler->DeleteClientFromMap(client.GetIp());
            break;
        }

        // invalid command -> should never happen
        // if(commands.find(command) == commands.end())
        // {
        //     SendMessage(client.GetSocket(), "\nInvalid Command. Try again");
        //     continue;
        // }
        
        // check if blocked
        if(_clientHandler->IsBlocked(client.GetIp()))
        {
            std::cout << userStruct.username << " is blocked." << std::endl;
            SendMessage(client.GetSocket(), "\nYou're currently blacklisted. Try again later");
            continue;
        }

        // check if logged in
        if(!client.LoggedIn() && command != "login")
        {
            SendMessage(client.GetSocket(), "\nYou need to be logged in first.");
            continue;
        }

        // commands
        if(command == "login")
        {
            std::string username = ReadOneLine(request);
            std::string password = ReadOneLine(request);

            std::cout << username << std::endl;
            std::cout << password << std::endl;

            userStruct.username = username;
            // ldap login
            SendMessage(client.GetSocket(), "OK");
            continue;
        }
        else if(command == "send")
        {
            
        }
        else if(command == "read")
        {
            
        }
        else if(command == "list")
        {
            
        }
        else if(command == "delete")
        {
            
        }

        // PrintErrorAndExitFail("Something went wrong.");
    }
    close(client.GetSocket());
}


void Server::StartServer(int backlog, const string& port)
{
    cout << "Starting Server" << endl;

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