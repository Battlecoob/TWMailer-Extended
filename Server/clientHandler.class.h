#include <map>
#include <iostream>

#include "clientStats.class.h"

#define MAX_FAILED_LOGIN 3
#define BLOCKED_TIME 60

class ClientHandler
{
private:
    std::map<int, ClientStats> _clientMap; // ip as key?

public:
    bool ExistsInMap(const std::string&);
    void AddClient2Map(const std::string& ip);
    void DeleteClientFromMap(const std::string& id);
};
