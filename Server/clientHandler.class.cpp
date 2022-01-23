#include "clientHandler.class.h"

using std::string;

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
    std::cout << "client added\n";
}

void ClientHandler::DeleteClientFromMap(const string& ip)
{
    // for (size_t i = 0; i < _clientMap.size(); i++)
    // {
    //     if(_clientMap[i].GetIp() == ip)
    //         _clientMap.erase(i);
    // }
    if(ExistsInMap(ip))
        _clientMap.erase(_clientMap.find(ip));
}