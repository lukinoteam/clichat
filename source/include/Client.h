#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <winsock2.h>
#include "Enums.h"
#include "FileHandle.h"
using namespace std;

class Client
{
  private:
    //MARK:- Connection data
    WSADATA WSAData;
    SOCKET serverSocket;
    SOCKADDR_IN clientAddr;
    //MARK:- Client's information
    string name;
    string ip;
    string roomId;
    Status status;
    Member role;

  public:
    Client(string name, Member role);
    void connectToServer(string serverIp);
    int sendMessage(char mess[]);
    void receiveMessage();
    void finish();
    void showName();

    //MARK:- getters
    string getName();
    string getRoomId();
    Status getStatus();
    Member getRole();
    void setRole(Member role);

    void setName(string name);

};
#endif
