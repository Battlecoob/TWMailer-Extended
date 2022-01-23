#include <map>
#include <vector>
#include <iostream>

#include "clientStats.class.h"

class ClientHandler
{
private:
    std::map<std::string, ClientStats> _clientMap = {};
        // irgendwas passt hier mitm default constr von ClientStats nicht

public:
    bool ExistsInMap(const std::string&);
    void AddClient2Map(const std::string&);
    const bool IsBlocked(const std::string&);
    void DeleteClientFromMap(const std::string&);
};
