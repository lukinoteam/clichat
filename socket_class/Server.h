#ifndef SERVER_H
#define SERVER_H
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <vector>
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
    Server();

  public:
    //MARK:- access data
    static Server * getInstance();
    string getRoomId();
    void start();
    void run();
    vector<SOCKET> getClients();
};
#endif