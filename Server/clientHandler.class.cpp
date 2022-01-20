#include "clientHandler.class.h"

using std::string;

bool ClientHandler::ExistsInMap(const string& ip)
{
    for (size_t i = 0; i < _clientMap.size(); i++)
    {
        if(_clientMap[i].GetIp() == ip)
            return true;
    }
    return false;
}

void ClientHandler::AddClient2Map(const string& ip)
{
    if(ExistsInMap(ip))
        return;

    ClientStats client(ip);

    int i = _clientMap.size();
    _clientMap.emplace(i, client); // .emplace() preferred for objects for efficiency
}

void ClientHandler::DeleteClientFromMap(const string& ip)
{
    for (size_t i = 0; i < _clientMap.size(); i++)
    {
        if(_clientMap[i].GetIp() == ip)
            _clientMap.erase(i);
    }
}