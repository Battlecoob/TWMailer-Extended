#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h> // close()
#include <sys/types.h>
#include <arpa/inet.h> // inet_aton()
#include <sys/socket.h> // socket(), bind(), ...
#include <netinet/in.h> // struct sockaddr_in

#include "../Other/functions.h"

class Client
{
private:
    int _sd;
    int _type; // SOCK_STREAM -> TCP
    int _domain; // AF_INET
    int _protocol; // 0

    bool _connected;
    bool _loggedIn;

    struct sockaddr_in _myAddr;
public:
    Client(int, int, int);
    ~Client();

    const bool IsConnected() { return _connected; }
    const bool IsLoggedIn() { return _loggedIn; }

    void PrintHelpMessage();
    
    std::string ReadMessage();
    void SendMessage(const std::string&);
    void Connect2Server(const std::string&, const std::string&);
    
    void ReadParamLine(const std::string&, std::string&, const std::size_t);
    void ReadParamMultiLine(const std::string&, std::string&);
};