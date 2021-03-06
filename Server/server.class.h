#include <string>
// #include <errno.h>
#include <cstring>
// #include <fcntl.h>
#include <set>
#include <iostream>
#include <unistd.h> // close()
#include <sys/types.h>
#include <arpa/inet.h> // inet_aton()
#include <sys/socket.h> // socket(), bind(), ...
#include <netinet/in.h> // struct sockaddr_in
#include <boost/algorithm/string.hpp> // to_lower_copy

// #include <set>
// #include <map>
// #include <thread>
// #include <sstream>
// #include <assert.h>

#include "ldap.class.h"
#include "../Other/functions.h"
#include "clientHandler.class.h"
#include "clientConnected.class.h"
#include "../Other/user.struct.cpp"
// #include "../Other/command.set.cpp"
// #include "messageHandler.class.h"

class Server
{
private:
    bool _listening;
    
    int _sd;
    int _type;
    int _domain;
    int _protocol;

    struct sockaddr_in _myAddr;
    socklen_t _addrlen;

    // MessageRepository* messageDb;
    // MessageHandler* _messageHandler;
    LDAPClass* _ldap;
    ClientHandler* _clientHandler;

public:
    Server(int, int, int, const std::string&); // domain, type, protocol, mailpool
    ~Server();
    
    std::set<std::string> commands = { "login", "send", "read", "list", "delete", "help", "quit"};
    
    const bool Listening() { return _listening; }
    
    std::string ReadMessage(int); // socket
    ClientConnected AcceptClient();
    void ClientThread(ClientConnected); // client
    bool ClientIsBlocked(const std::string&);
    void StartServer(int, const std::string&); // backlog, port
    void SendMessage(int, const std::string&); // socket message
};
