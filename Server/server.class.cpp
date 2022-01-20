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

}

Server::~Server()
{
    close(_sd);
}

string Server::ReadMessage(int socket)
{
    cout << "Not Implemented" << endl;
    return "Not Implemented";
}

ClientConnected Server::AcceptClient()
{
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    socklen_t addrlen = sizeof(clientAddr);
    int socket = accept(_sd, (struct sockaddr*)&clientAddr, &addrlen);

    std::cout << "Client connected." << std::endl;
    return ClientConnected(socket, inet_ntoa(clientAddr.sin_addr));
}

void Server::ClientThread(ClientConnected client)
{
    
}

void Server::StartServer(int backlog, const string& port)
{
    std::cout << "Starting Server" << std::endl;

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
}

void Server::SendMessage(int socket, const std::string& message)
{
    cout << "Not Implemented" << endl;
}