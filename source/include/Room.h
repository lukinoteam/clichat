#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>
#include "Owner.h"
#include <ctime>
#include <sstream>

using namespace std;


class Room
{
    public:
        Room();
        Room(string owner, string rule);
        virtual ~Room();
        string getIP();
        void setIP(string str);
        int getPort();
        void setPort(int n);
        string getOwner();
        string getTimeCreate();
        string getRule();
        string getRoomInfo();
        void setOwner(string owner);
        void setRule(string rule);

    private:
        string owner;
        string ip;
        int port;
        string timeCreate;
        string rule;


};

#endif // ROOM_H
