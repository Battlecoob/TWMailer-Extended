#include "clientHandler.class.h"

using std::string;

void ClientHandler::AddFailedLoginAttempt(const string& ip)
{
    _clientMap.at(ip).IncrFailedAttempts();
}

const bool ClientHandler::IsBlocked(const string& ip)
{
    return _clientMap.at(ip).IsBlocked();
}

bool ClientHandler::ExistsInMap(const string& ip)
{
    return (_clientMap.find(ip) != _clientMap.end()) ? true : false;
}

void ClientHandler::AddClient2Map(const string& ip)
{
    if(ExistsInMap(ip))
        return;

    ClientStats client;

    _clientMap.insert(std::pair<std::string, ClientStats>{ip, client});
}

void ClientHandler::DeleteClientFromMap(const string& ip)
{
    if(ExistsInMap(ip))
        _clientMap.erase(_clientMap.find(ip));
}