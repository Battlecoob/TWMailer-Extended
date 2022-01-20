#include <iostream>
#include <unistd.h> // close()

class ClientConnected
{
private:
    int _sd;
    bool _loggedIn;
    std::string _ip;

public:
    ClientConnected(int, const std::string&); // socket, ip

    const int GetSocket() { return _sd; }
    const bool LoggedIn() { return _loggedIn; }
    const std::string GetIp() { return _ip; }

    void Disconnect();
    void Login() { _loggedIn = true; }
};