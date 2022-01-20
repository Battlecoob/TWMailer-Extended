#include <map>
#include <iostream>

#include "clientStats.class.h"

class ClientHandler
{
private:
    std::map<int, ClientStats> _clientMap; // ip as key?
        // irgendwas passt hier mitm default constr von ClientStats nicht

public:
    bool ExistsInMap(const std::string&);
    void AddClient2Map(const std::string& ip);
    void DeleteClientFromMap(const std::string& id);
};
