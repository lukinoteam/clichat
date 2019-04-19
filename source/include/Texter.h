#ifndef TEXTER_H
#define TEXTER_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>
#include "ControlCenter.h"

#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Client.h"
#include "FileHandle.h"
#include "Enums.h"


using namespace std;

class Texter
{
    public:
        Texter(string name, Member role, string ip);
        virtual ~Texter();
        void run();
        void sendThread();
        void receiveThread();
        int getStatus();
        void setStatus(int status);
        void sendToServer(string message);
        void messageHandle(string message);
    private:
        int joined = 0;
        ControlCenter *control;
        Client *client;
};

#endif // TEXTER_H
