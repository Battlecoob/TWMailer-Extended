/*
***************************************************************************************************
This file includes files that are used across multiple classes
***************************************************************************************************
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string.h>
#include <iostream>
#include <unistd.h> // read()


#define BUF 1024

void PrintSuccAndExitSucc(int);
void PrintErrorAndExitFail(const std::string&);

std::string ReadLineSocket(int);
std::string ReadOneLine(std::string&);
std::string ReadNBytesSocket(int, int);

void SendNBytesSocket(int, int, const std::string&);

#endif