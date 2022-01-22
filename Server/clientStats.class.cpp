#include "clientStats.class.h"

ClientStats::ClientStats()
{
    // _ip = "";
    _blocked = false;
    _failedCounter = 0;
}

// ClientStats::ClientStats(std::string ip)
// {
//     _ip = ip;
//     _blocked = false;
//     _failedCounter = 0;
// }

const bool ClientStats::IsBlocked()
{
    if(_failedCounter < MAX_FAILED_LOGIN)
        return _blocked = false;
    
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - _timeStartBeingBlocked).count();
    
    if(duration >= BLOCKED_TIME)
    {
        ResetAttempts();
        return _blocked = false;
    }

    return _blocked = true;
}

// void ClientStats::SetIp(std::string ip)
// {
//     if(_ip.empty())
//         _ip = ip;
// }

void ClientStats::IncrFailedAttempts()
{
    _failedCounter++;
    if(_failedCounter >= MAX_FAILED_LOGIN)
        _timeStartBeingBlocked = std::chrono::high_resolution_clock::now();
}