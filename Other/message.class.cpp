#include "message.class.h"

using std::cout; using std::endl;
using std::string;

Message::Message(std::string sender, std::string recipient, std::string subject, std::string message)
{
    _sender = sender;
    _subject = subject;
    _message = message;
    _recipient = recipient;

    if(_sender.size() > 8 || _sender.size() < 1)
        throw std::invalid_argument("_sender must have less than 9 char.");

    if(_recipient.size() > 8 || _recipient.size() < 1)
        throw std::invalid_argument("_recipient must have less than 9 char.");
    
    if(_subject.size() > 80 || _subject.size() < 1)
        throw std::invalid_argument("_subject must have less than 81 char.");
}

Message::Message(std::string text)
{
    _sender = ReadOneLine(text);
    _subject = ReadOneLine(text);
    _recipient = ReadOneLine(text);
    _message = text;
    
    if(_sender.size() > 8 || _sender.size() < 1)
        throw std::invalid_argument("_sender must have less than 9 char.");

    if(_recipient.size() > 8 || _recipient.size() < 1)
        throw std::invalid_argument("_recipient must have less than 9 char.");
    
    if(_subject.size() > 80 || _subject.size() < 1)
        throw std::invalid_argument("_subject must have less than 81 char.");
}

const string Message::ToMail()
{
    string text = "";
    
    text += "Sender " + _sender + "\n";
    text += "Recipient " + _recipient + "\n";
    text += "Subject " + _subject + "\n";
    text += "Message " + _message + "\n";

    return text;
}

const string Message::ToString()
{
    return _sender + '\n' + _recipient + '\n' + _subject + "\n" + _message; 
}