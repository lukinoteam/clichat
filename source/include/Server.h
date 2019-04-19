#ifndef SERVER_H
#define SERVER_H
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <vector>
#include "Room.h"
#include "FileHandle.h"

using namespace std;
class Server
{
  private:
    //MARK:- Connection data
    string roomId;
    WSADATA WSAData;
    SOCKET serverSocket;
    SOCKADDR_IN serverAddr;
    vector<SOCKET> clients;
    void setRoomId();
    //MARK:- Singleton object
    static Server *instance;
    //MARK:- private constructor to prevent outside initiation
    Room *room;


  public:
    Server();
    //MARK:- access data
    static Server * getInstance();
    string getRoomId();
    void start(string owner, string rule);
    void run();
    vector<SOCKET> getClients();
    void finish();
    Room* getRoom();
};
#endif
