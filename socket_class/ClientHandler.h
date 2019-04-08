#ifndef HANDLER_H
#define HANDLER_H
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
using namespace std;

class ClientHandler
{
  private:
    SOCKET clientSocket;
    HANDLE handler;
    DWORD threadID;
    DWORD WINAPI handle(LPVOID lpParameter);
  public:
    ClientHandler(SOCKET clientSocket);
    ~ClientHandler();
    void receiveMessage(void * data);
    void sendMessage(string message);
    
};
#endif