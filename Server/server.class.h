#include <string>
// #include <errno.h>
// #include <cstring>
// #include <fcntl.h>
#include <iostream>
// #include <unistd.h> // close()
#include <sys/types.h>
#include <arpa/inet.h> // inet_aton()
#include <sys/socket.h> // socket(), bind(), ...
#include <netinet/in.h> // struct sockaddr_in

// #include <set>
// #include <map>
// #include <thread>
// #include <sstream>
// #include <assert.h>

class Server
{
private:
    bool _listening;
    int _sd;
    int _domain;
    int _type;
    int _protocol;

    struct sockaddr_in _myAddr;
    socklen_t _addrlen;


public:
    Server(/* args */);
    ~Server();
};
