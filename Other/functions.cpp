#include "functions.h"

using std::cout; using std::endl; 
using std::string; using std::cerr;

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

string ReadOneLine(string& text)
{
    string line = "";
    size_t position;

    for (position = 0; position < text.size(); position++)
    {
        if(text.at(position) == '\n')
            break;
        
        line.push_back(text.at(position));
    }
    
    text = text.substr(0, position);
    return line;
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