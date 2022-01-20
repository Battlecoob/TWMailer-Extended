#include <iostream>

#include "functions.h"

class Message
{
private:
    /* data */
    std::string _sender;
    std::string _message;
    std::string _subject;
    std::string _recipient;

public:
    Message(std::string, std::string, std::string, std::string);
    Message(std::string); // gets one text var with all information

    const std::string GetSender() { return _sender; };
    const std::string GetMessage() { return _message; };
    const std::string GetSubject() { return _subject; };
    const std::string GetRecipient() { return _recipient; };

    const std::string ToMail(); // mal schauen ob ich die brauch / nehm -> scho auffaellig
    const std::string ToString();
};