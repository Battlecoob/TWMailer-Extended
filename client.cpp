// #include <errno.h>
#include <signal.h>
#include <iostream>
// #include <stdexcept>
// #include <arpa/inet.h>
// #include <netinet/in.h>
// #include <sys/socket.h>
// #include <sys/types.h>

#include "Other/functions.h"
#include "Client/client.class.h"



int main(int argc, char** argv)
{
    std::string userCmd;
    // Session session;
    // InputValidator.reader(std::cin);

    if(argc != 3)
        PrintErrorAndExitFail("Invalid amount of arguments:\nUsage: ./client <ip4-address> <port>.");

    std::cout << "Trying to connect to Server with ip: " << argv[1] << " and port: " << argv[2] << "." << std::endl;

    Client client(AF_INET, SOCK_STREAM, 0);

    signal(SIGINT, PrintSuccAndExitSucc);

    // if( (on_exit(cleanUp, (void*)&client)) != 0 )
    //     error_and_die("error registering exit handler");

    client.Connect2Server(argv[1], argv[2]); // ip, port

    client.PrintHelpMessage();

    while(true)
    {

    }

    return 0;
}