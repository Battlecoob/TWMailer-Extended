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
    cout << "Valid Commands include: login | send | read | list | delete | help | quit" << endl;
}

string Client::ReadMessage()
{
    if(!_connected)
        return "";

    string message;

    int messageSize = std::stoi(ReadLineSocket(_sd));
    if (messageSize)
        return message = ReadNBytesSocket(_sd, messageSize);

    return message = "Nothing sent from server.";
}

void Client::SendMessage(const string& text)
{
    if(!_connected)
        return;

    // send size of message
    // (socket, size of the stringsize , size of text)
    SendNBytesSocket(_sd, std::to_string(text.size()).size() + 1, std::to_string(text.size()) + '\n');
    // send message
    SendNBytesSocket(_sd, text.size(), text);
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



void Client::ReadParamLine(const string& param, string& target, const std::size_t maxLen)
{
    while (true)
    {
        std::cout << "Enter " << param << " (max Characters: " << maxLen << "): ";
        std::getline(std::cin, target);

        if(target.size() <= maxLen)
            break;

        std::cout << "Invalid input." << std::endl;
    }
}

void Client::ReadParamMultiLine(const string& param, string& target)
{
    std::cout << "Enter " << param << "('.' ends the command): ";
    
    std::string tmp;
    
    while (true)
    {
        std::string line;
        std::getline(std::cin, line);

        if(line == ".")
            break;
        
        tmp += line + '\n';
    }
    
    target = tmp;
}