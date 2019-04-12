#include <string>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include "Enums.h"
#include <vector>
#include <process.h>
#include "Server.h"
#include "ClientHandler.h"

using namespace std;

void threadOnNewSocket(void *data);
//MARK:- Constructor
ClientHandler::ClientHandler(SOCKET clientSocket, Server *server)
{
    this->clientSocket = clientSocket;
    this->server = server;
    this->handler = (HANDLE)_beginthread(&threadOnNewSocket, 0, (void *)this);
}

//MARK:- Destructor
ClientHandler::~ClientHandler()
{
    //TO-DO: close thread which handles new socket transaction
    CloseHandle(this->handler);
}

//MARK:- Getter:
SOCKET ClientHandler::getClientSockt()
{
    return this->clientSocket;
}

Server *ClientHandler::getServer()
{
    return this->server;
}
//MARK:- Thread created to handle new socket transaction with var @data = incoming socket
void threadOnNewSocket(void *data)
{
    while (true)
    {

        char buffer[1024];
        ClientHandler *handler = (ClientHandler *)data;
        SOCKET clientSocket = handler->getClientSockt();
        Server *server = handler->getServer();
        vector<SOCKET> clients = server->getClients();
        cout << "Client connected!" << endl;
        
        //Function to receive message from socket
        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << "Client says: " << buffer << endl;
        //Broadcast:
        for (size_t i = 0; i < clients.size(); ++i)
        {
            send(clients[i], buffer, sizeof(buffer), 0);
        }
        //Reset char array
        memset(buffer, 0, sizeof(buffer));
    }
}
