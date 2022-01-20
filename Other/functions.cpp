/*
***************************************************************************************************
This file includes files that are used across multiple classes
***************************************************************************************************
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>

#define BUF 1024

using std::string;

void ReadLineSocket(int);
void SendNBytesSocket(int);
void PrintSuccAndExitSucc();
void ReadNBytesSocket(int, int);
void PrintErrorAndExitFail(const string&); // ref

#endif