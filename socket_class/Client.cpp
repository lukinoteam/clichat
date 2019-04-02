#include <string>
#include <iostream>
#include <sstream>
#include <winsock2.h>
#include "Enums.h"
#include "Client.h"
using namespace std;

//MARK:- public initialization
Client::Client(string name, Member role)
{
    this->name = name;
    this->status = ONLINE;
    this->role = role;
    WSAStartup(MAKEWORD(2,0), &this->WSAData);
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
}
//MARK:- Function:
void Client::connectToServer(string serverIp) {
    const char * ip = serverIp.c_str();
    this->clientAddr.sin_addr.s_addr = inet_addr(ip);
    this->clientAddr.sin_family = AF_INET;
    this->clientAddr.sin_port = htons(5555);
    connect(serverSocket, (SOCKADDR *)&clientAddr, sizeof(clientAddr));
}

void Client::sendMessage(char buffer[]) {
    send(serverSocket, buffer, sizeof(&buffer) * strlen(buffer), 0);
}

void Client::finish() {
    closesocket(serverSocket);
    WSACleanup();
}
//MARK:- getters
string Client::getName() {
    return this->name;
}
string Client::getRoomId() {
    return this->roomId;
}
Status Client::getStatus() {
    return this->status;
}
Member Client::getRole() {
    return this->role;
}
