#ifndef HANDLER_H
#define HANDLER_H
#include <string>
#include "Server.h"
#include <winsock2.h>
#include <windows.h>
#include <iostream>
using namespace std;

class ClientHandler
{
  private:
    SOCKET clientSocket;
    HANDLE handler;
    Server *server;
    DWORD threadID;
    DWORD WINAPI handle(LPVOID lpParameter);

  public:
    ClientHandler(SOCKET clientSocket, Server *server);
    ~ClientHandler();
    void receiveMessage(void *data);
    void sendMessage(string message);
    SOCKET getClientSockt();
    Server* getServer();
};
#endif