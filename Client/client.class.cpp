#include "client.class.h"

using std::cout; using std::endl;
using std::cerr; using std::string;

Client::Client(int domain, int type, int protocol)
{
    _type = type;
    _domain = domain;
    _protocol = protocol;

    _sd = -1;
    _loggedIn = false;
    _connected = false;

    if((_sd = socket(_domain, _type, _protocol)) < 0)
        PrintErrorAndExitFail("Error while creating socket.");
}

Client::~Client()
{
    SendMessage("quit");
    close(_sd);
}

void Client::PrintHelpMessage()
{
    cout << "Valid Commands include:\nlogin | send | read | list | delete | help" << endl;
    cout << "To Exit the program type 'quit'" << endl;
}

string Client::ReadMessage()
{
    cout << "Not Implemented" << endl;
    return "Not Implemented";
}

void Client::SendMessage(const std::string& text)
{
    cout << "Not Implemented" << endl;
}

void Client::Connect2Server(const string& ip, const string& port)
{
    if (_connected)
        close(_sd);

    memset(&_myAddr, 0, sizeof(_myAddr));
    _myAddr.sin_family = _domain;

    try
    {
        _myAddr.sin_port = htons(std::stoi(port));
    }
    catch(...)
    {
        cerr << "Error while converting port (htons)" << endl;
    }

    // ip.data() -> inet_aton() verlangt einen const char pointer
    if(inet_aton(ip.data(), &_myAddr.sin_addr) == 0)
        PrintErrorAndExitFail("Error while converting ip to address data structure.");
    
    if((connect(_sd, (struct sockaddr*)&_myAddr, sizeof(_myAddr))) < 0)
        PrintErrorAndExitFail("Error while connecting to server.");

    _connected = true;
}