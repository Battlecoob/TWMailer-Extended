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
    int len;
    char buffer;
    string line = "";

    while (true)
    {
        // read() because it's more generic and I don't need the additional options from recv()
        if((len = read(sd, &buffer, 1)) == 1)
        {
            if(buffer != '\n')
                line.push_back(buffer);

            break;
        }
        else if(len == -1)
            PrintErrorAndExitFail("Error while reading from Socket.");
        
        else if(len == 0)
            return "0";
    }

    return line;    
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
    std::cout << "in ReadNBytesSocket" << std::endl;
    int len;
    int bytesLeft = n;
    int bytesRead = 0;
    char buffer[n+1];

    memset(buffer, 0, n+1);

    while(bytesLeft > 0)
    {
        if((len = read(sd, buffer + bytesRead, bytesLeft)) == 1)
        {
            bytesRead++;
            bytesLeft--;
        }
        else if(len == -1)
            PrintErrorAndExitFail("Error while reading from Socket.");
        
        else if(len == 0)
            return "0";
    }
    buffer[n] = '\0';

    return string(buffer);
}

void SendNBytesSocket(int sd, int n, const std::string& text)
{
    cout << "Not Implemented" << endl;
}