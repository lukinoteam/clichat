#include <iostream>
#include <string>
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Server.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;
Server *Server::instance = NULL;
Server::Server()
{
  WSAStartup(MAKEWORD(2, 0), &this->WSAData);
  this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  this->serverAddr.sin_addr.s_addr = INADDR_ANY;
  this->serverAddr.sin_family = AF_INET;
  this->serverAddr.sin_port = htons(5555);
  setRoomId();
}
Server *Server::getInstance()
{
  if (instance == NULL)
  {
    instance = new Server();
  }
  return instance;
}

void Server::setRoomId()
{
  char szHostName[255];
  gethostname(szHostName, 255);
  struct hostent *host_entry;
  host_entry = gethostbyname(szHostName);
  roomId = inet_ntoa(*(struct in_addr *)*host_entry->h_addr_list);
}
string Server::getRoomId()
{
  return this->roomId;
}
void Server::start()
{
  bind(serverSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
  listen(serverSocket, 0);
  cout << "Server started..." << endl;
}
void Server::run()
{
  SOCKET client;
  SOCKADDR_IN clientAddr;
  char buffer[1024];
  int clientAddrSize = sizeof(clientAddr);
  cout << "Server is running" << endl;

  while (true)
  {
    if ((client = accept(serverSocket, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {
      cout << "Client connected!" << endl;
      recv(client, buffer, sizeof(buffer), 0);
      cout << "Client says: " << buffer << endl;
      memset(buffer, 0, sizeof(buffer));

      closesocket(client);
      cout << "Client disconnected." << endl;
    }
  }
}
