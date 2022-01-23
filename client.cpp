// #include <errno.h>
#include <signal.h>
#include <iostream>
// #include <stdexcept>
// #include <arpa/inet.h>
// #include <netinet/in.h>
// #include <sys/socket.h>
// #include <sys/types.h>
#include <boost/algorithm/string.hpp>

#include "Other/functions.h"
#include "Client/client.class.h"
#include "Other/command.set.cpp"



int main(int argc, char** argv)
{
    std::string userCommandUnformated;
    // Session session;
    // InputValidator.reader(std::cin);

    if(argc != 3)
        PrintErrorAndExitFail("Invalid amount of arguments:\nUsage: ./client <ip4-address> <port>.");

    std::cout << "Trying to connect to Server with ip: " << argv[1] << " and port: " << argv[2] << "." << std::endl;

    Client client(AF_INET, SOCK_STREAM, 0);

    signal(SIGINT, PrintSuccAndExitSucc);

    client.Connect2Server(argv[1], argv[2]); // ip, port
    client.PrintHelpMessage();

    while(true)
    {
        std::string send;
        std::cout << "enter a command: ";
        std::getline(std::cin, userCommandUnformated);
        
        
        try
        {
            std::string response;

            if(commands.find(userCommandUnformated) == commands.end())
            {
                std::cout << "\n\nInvalid Command" << std::endl;
                client.PrintHelpMessage();
                continue;
            }

            std::string userCommand = boost::algorithm::to_lower_copy(userCommandUnformated);
            
            if (userCommand == "login")
            {
                client.SendMessage(userCommand);
                response = client.ReadMessage();
                std::cout << response << std::endl;

                response = client.ReadMessage();
                std::cout << response << std::endl;
            }
            else if(userCommand == "send")
            {
                client.SendMessage(userCommand);
                response = client.ReadMessage();
                std::cout << response << std::endl;

            }
            else if(userCommand == "read")
            {
                client.SendMessage(userCommand);
                response = client.ReadMessage();
                std::cout << response << std::endl;

            }
            else if(userCommand == "list")
            {
                client.SendMessage(userCommand);
                response = client.ReadMessage();
                std::cout << response << std::endl;

            }
            else if(userCommand == "delete")
            {
                client.SendMessage(userCommand);
                response = client.ReadMessage();
                std::cout << response << std::endl;

            }
            else if(userCommand == "quit")
            {
                client.SendMessage(userCommand);
                response = client.ReadMessage();
                std::cout << response << std::endl;

            }
            else
            {
                throw std::invalid_argument("invalid input");
            }
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        
    }

    return 0;
}