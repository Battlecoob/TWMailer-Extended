#include <signal.h>
#include <iostream>

#include "Other/functions.h"
#include "Server/server.class.h"

#define BACKLOG 5

int main(int argc, char** argv)
{
    if(argc != 3)
        PrintErrorAndExitFail("Invalid amount of arguments:\nUsage: ./server <port> <mail-spool-directoryname>.");

    Server server(AF_INET, SOCK_STREAM, 0, argv[2]); // argv[2]: mailpool
    
    signal(SIGINT, PrintSuccAndExitSucc);

    server.StartServer(BACKLOG, argv[1]);
    std::cout << "Listening on port: " << argv[1] << ".\n";

    while (true)
    {
        // connect client
        ClientConnected client = server.AcceptClient();
        // start thread with that client
    }

    exit(EXIT_SUCCESS);
}