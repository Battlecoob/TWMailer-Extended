// #include <errno.h>
#include <set>
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
// #include "Other/command.set.cpp"


int main(int argc, char** argv)
{
    std::string userCommandUnformated;
    // Session session;
    // InputValidator.reader(std::cin);
    std::set<std::string> commands = { "login", "send", "read", "list", "delete", "help", "quit"};

    if(argc != 3)
        PrintErrorAndExitFail("Invalid amount of arguments:\nUsage: ./client <ip4-address> <port>.");

    std::cout << "\nTrying to connect to Server with ip: " << argv[1] << " and port: " << argv[2] << "." << std::endl;

    Client client(AF_INET, SOCK_STREAM, 0);

    signal(SIGINT, PrintSuccAndExitSucc);

    client.Connect2Server(argv[1], argv[2]); // ip, port
    
    // check if client could connect to server
    std::string response = client.ReadMessage();
    if(ReadOneLine(response) == "ERR")
        PrintErrorAndExitFail(ReadOneLine(response));

    std::cout << response << std::endl;
    client.PrintHelpMessage();

    while(true)
    {
        std::string send;
        std::cout << "enter a command: ";
        std::getline(std::cin, userCommandUnformated);
        
        try
        {

            if(commands.find(userCommandUnformated) == commands.end())
            {
                std::cout << "\nInvalid Command" << std::endl;
                client.PrintHelpMessage();
                continue;
            }

            std::string userCommand = boost::algorithm::to_lower_copy(userCommandUnformated);
            
            if (userCommand == "login")
            {
                std::string username, password;
                
                client.ReadParamLine("Username", username, 8);
                client.ReadParamLine("Password", password, 100);
                
                //TEST
                send += "login\n";
                send += username + "\n";
                send += password;

                client.SendMessage(send);
                response = client.ReadMessage();
                std::string tmp = ReadOneLine(response);
                std::cout << tmp << std::endl; // ERR | OK
                
                tmp = ReadOneLine(response);
                if(tmp != "ERR" && tmp != "OK") // blocked
                {
                    std::cout << tmp << std::endl;
                    break;
                }
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
                break;
            }
            else if(userCommand == "help")
            {
                client.PrintHelpMessage();
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
    // close client socket?
    exit(EXIT_SUCCESS);
}