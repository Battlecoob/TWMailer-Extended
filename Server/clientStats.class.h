#include <chrono>
#include <iostream>

#define BLOCKED_TIME 60
#define MAX_FAILED_LOGIN 3

class ClientStats
{
private:
    bool _blocked;
    std::string _ip;
    int _failedCounter;
    std::chrono::_V2::system_clock::time_point _timeStartBeingBlocked;

public:
    ClientStats();
    ClientStats(std::string);

    const bool IsBlocked();
    void IncrFailedAttempts();
    void SetIp(std::string ip) { _ip = ip; }
    const std::string GetIp() { return _ip; }
    void ResetAttempts() { _failedCounter = 0; }
    const int FailedAttempts() { return _failedCounter; }
};