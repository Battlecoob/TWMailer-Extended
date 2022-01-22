#include "clientHandler.class.h"

using std::string;

bool ClientHandler::ExistsInMap(const string& ip)
{
    // for (size_t i = 0; i < _clientMap.size(); i++)
    // {
    //     if(_clientMap[i].GetIp() == ip)
    //         return true;
    // }
    // std::cout << "in existsinmap\n";
    // bool b = _clientMap.empty();
    // std::cout << b << std::endl;
    // if(_clientMap.find(ip) != _clientMap.end())
    //     b = true;
    // else
    //     b = false;

    // std::cout << b << std::endl;
    return (_clientMap.find(ip) != _clientMap.end()) ? true : false;
}

void ClientHandler::AddClient2Map(const string& ip)
{
    if(ExistsInMap(ip))
        return;

    ClientStats client;

    // _clientMap.emplace(ip, client); // .emplace() preferred for objects for efficiency
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