#include <string>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include "Enums.h"
#include <process.h>
#include "ClientHandler.h"

using namespace std;

void threadOnNewSocket(void *data);
//MARK:- Constructor
ClientHandler::ClientHandler(SOCKET clientSocket)
{
    this->clientSocket = clientSocket;
    this->handler = (HANDLE)_beginthread(&threadOnNewSocket, 0, (void *)this->clientSocket);
}

//MARK:- Destructor
ClientHandler::~ClientHandler()
{
    //TO-DO: close thread which handles new socket transaction
    CloseHandle(this->handler);
}
//MARK:- Thread created to handle new socket transaction with var @data = incoming socket
void threadOnNewSocket(void *data)
{
    while (true)
    {

        char buffer[1024];
        SOCKET clientSocket = (SOCKET)data;
        cout << "Client connected!" << endl;
        //Function to receive message from socket
        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << "Client says: " << buffer << endl;
        //Reset char array
        memset(buffer, 0, sizeof(buffer)); 
    }
}
//MARK:-Message Receiver
void ClientHandler::receiveMessage(void *data)
{
    SOCKADDR_IN clientAddr;
    char buffer[1024];
    int clientAddrSize = sizeof(clientAddr);
    cout << "Client connected!" << endl;
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "Client says: " << buffer << endl;
    memset(buffer, 0, sizeof(buffer));
}
