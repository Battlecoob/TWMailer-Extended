#include <map>
#include <iostream>

#include "clientStats.class.h"

class ClientHandler
{
private:
    std::map<int, ClientStats> _clientMap; // ip as key?

public:
    bool ExistsInMap(const std::string&);
    void AddClient2Map(const std::string& ip);
    void DeleteClientFromMap(const std::string& id);
};
