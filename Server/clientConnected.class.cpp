#include "clientConnected.class.h"

ClientConnected::ClientConnected(int socket, const std::string& ip)
{
    _ip = ip;
    _sd = socket;
    _loggedIn = false;
}

void ClientConnected::Disconnect()
{
    close(_sd);
    _loggedIn = false;
}