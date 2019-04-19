#include <iostream>
#include <string>
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Server.h"
#include <vector>
#include "ClientHandler.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

//MARK:- Private instance of Singleton Class
Server *Server::instance = NULL;

//MARK:- Private constructor to create server and listening socket
Server::Server()
{
  WSAStartup(MAKEWORD(2, 0), &this->WSAData);
  this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  this->serverAddr.sin_addr.s_addr = INADDR_ANY;
  this->serverAddr.sin_family = AF_INET;
  this->serverAddr.sin_port = htons(5555);
  setRoomId();


}
//MARK:- Publicly access to instance
Server *Server::getInstance()
{
  if (instance == NULL)
  {
    instance = new Server();
  }
  return instance;
}

//MARK:- Setter
void Server::setRoomId()
{
  char szHostName[255];
  gethostname(szHostName, 255);
  struct hostent *host_entry;
  host_entry = gethostbyname(szHostName);
  roomId = inet_ntoa(*(struct in_addr *)*host_entry->h_addr_list);
}

//MARK:- Getter
string Server::getRoomId()
{
  return this->roomId;
}

vector<SOCKET> Server::getClients() {
  return this->clients;
}

//MARK:- Start server
void Server::start(string owner, string rule)
{
  //TO-DO: initiating socket
  bind(serverSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

  //TO-DO: make socket listening
  listen(serverSocket, 0);

    this->room = new Room(owner, rule);
    cout << "--- Room Info ---" << endl;
    cout << "Owner: " << owner << "\tRule: " << rule << "\tTime create: " << this->room->getTimeCreate() << endl;
    cout << "Server started..." << endl;

    FileHandle* fileHandle = new FileHandle();
    fileHandle->removeData("","ModList.txt","");
    fileHandle->removeData("","BanList.txt","");
    fileHandle->removeData("","ClientList.txt","");

    delete fileHandle;


}

//MARK:- close socket
void Server::finish()
{
    closesocket(serverSocket);
    WSACleanup();
}

//MARK:- Run after server started
void Server::run()
{
  SOCKET client;
  SOCKADDR_IN clientAddr;
  char buffer[1024];
  int clientAddrSize = sizeof(clientAddr);
  cout << "Server is running" << endl;

  while (true)
  {
    //TO-DO: listen and accept new socket connection
    if ((client = accept(serverSocket, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {
      this->clients.push_back(client);
      //TO-DO: create new socket handler to handle incoming socket
      ClientHandler * handler = new ClientHandler(client, this->getInstance());
    }
  }
}

Room* Server::getRoom(){
    return room;
}
