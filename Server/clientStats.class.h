#include <chrono>
#include <iostream>

#define BLOCKED_TIME 60
#define MAX_FAILED_LOGIN 3

class ClientStats
{
private:
    bool _blocked;
    int _failedCounter;
    std::chrono::_V2::system_clock::time_point _timeStartBeingBlocked;

public:
    ClientStats();

    const bool IsBlocked();
    void IncrFailedAttempts();
    void ResetAttempts() { _failedCounter = 0; }
    const int FailedAttempts() { return _failedCounter; }
};