#include "functions.h"

using std::cout; using std::endl; 
using std::string;

void PrintSuccAndExitSucc(int signal)
{
    cout << "Exit Client" << endl;
    exit(EXIT_SUCCESS);
}

void PrintErrorAndExitFail(const string& err)
{
    cout << err << endl;
    exit(EXIT_FAILURE);
}

string ReadLineSocket(int sd)
{
    return "Not Implemented";
}

string ReadLine(string& text)
{
    cout << "Not Implemented" << endl;
    return "Not Implemented";
}

string ReadNBytesSocket(int sd, int n)
{
    cout << "Not Implemented" << endl;
    return "Not Implemented";
}

void SendNBytesSocket(int sd, int n, const std::string& text)
{
    cout << "Not Implemented" << endl;
}