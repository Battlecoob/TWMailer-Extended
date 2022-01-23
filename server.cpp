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
    std::cout << "\nListening on port: " << argv[1] << ".\n";

    while (true)
    {
        ClientConnected client = server.AcceptClient();

        if(!server.ClientIsBlocked(client.GetIp()))
        {
            std::cout << "Client connected from: " << client.GetIp() << std::endl;
            server.SendMessage(client.GetSocket(), "OK\nYou're successfully connected to the Mail-Server.");
            // start thread with that client
            server.ClientThread(client); // not yet threaded
        }
        else
        {
            server.SendMessage(client.GetSocket(), "ERR\nYou're currently blacklisted for up to a minute. Try again later");
            continue;
        }
        
    }

    exit(EXIT_SUCCESS);
}