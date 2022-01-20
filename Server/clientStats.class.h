#include <iostream>

class ClientStats
{
private:
    bool blocked;
    std::string _ip;
    int _failedCounter;

public:
    ClientStats() {}
    ClientStats(std::string ip) { _ip = ip; }

    void SetIp(std::string ip) { _ip = ip; }
    const std::string GetIp() { return _ip; }
    const bool IsBlocked() { return blocked; }
    void ResetAttempts() { _failedCounter = 0; }
    void InrFailedAttempts() { _failedCounter++; }
    const int FailedAttempts() { return _failedCounter; }
};