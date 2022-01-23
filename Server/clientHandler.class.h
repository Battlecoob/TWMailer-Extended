#include <map>
#include <vector>
#include <iostream>

#include "clientStats.class.h"

class ClientHandler
{
private:
    std::map<std::string, ClientStats> _clientMap = {};

public:
    bool ExistsInMap(const std::string&);
    void AddClient2Map(const std::string&);
    const bool IsBlocked(const std::string&);
    void DeleteClientFromMap(const std::string&);
    void AddFailedLoginAttempt(const std::string&);
};
