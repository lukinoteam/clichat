#include <string>
#include <iostream>
#include <winsock2.h>
#include "Enums.h"
#include "Client.h"
using namespace std;

char* stringToCharArray(string str);

//MARK:- public initialization
Client::Client(string name, Member role)
{
    this->name = name;
    this->status = ONLINE;
    this->role = role;
    WSAStartup(MAKEWORD(2, 0), &this->WSAData);
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
}
//MARK:- Function:
void Client::connectToServer(string serverIp)
{
    const char *ip = serverIp.c_str();
    this->clientAddr.sin_addr.s_addr = inet_addr(ip);
    this->clientAddr.sin_family = AF_INET;
    this->clientAddr.sin_port = htons(5555);
    connect(serverSocket, (SOCKADDR *)&clientAddr, sizeof(clientAddr));
}

//MARK:- Message Sender
int Client::sendMessage(char* buffer)
{
    int iResult;
    iResult = send(serverSocket, buffer, sizeof(&buffer) * strlen(buffer), 0);
    return iResult;
}

void Client::receiveMessage(){
    char szBuffer[1024];

    int nLength;
    nLength = recv(serverSocket, szBuffer, sizeof(&szBuffer) * 100, 0);
    if (nLength > 0)
    {
        szBuffer[nLength - 1] = '\0';

        string str(szBuffer);



        if (str.substr(0,9).compare("send_info") == 0){
            cout << str.substr(10, str.length()) << endl;
            return;
        }
        else if (str.substr(0,9).compare("send_mods") == 0){
            cout << "---Moderator List:" << endl;
            cout << str.substr(11, str.length()) << endl;
            return;
        }
        else if (str.substr(0,12).compare("send_filters") == 0){
            cout << "---Filter List:" << endl;
            cout << str.substr(14, str.length()) << endl;
            return;
        }
        else if (str.substr(0,11).compare("send_report") == 0){
            cout << "---Client List:" << endl;
            cout << str.substr(13, str.length()) << endl;
            return;
        }
        else if (str.substr(0,7).compare("setmod:") == 0){
            if (str.substr(7, str.length()).compare(this->getName()) == 0)
                this->setRole(MOD);
            else
                return;
        }

        else if (str.substr(0,9).compare("setunmod:") == 0){
            if (str.substr(9, str.length()).compare(this->getName()) == 0)
                this->setRole(MEM);
            else
                return;

        }
        else if (str.substr(0,7).compare("setban:") == 0){
            if (str.substr(7, str.length()).compare(this->getName()) == 0)
                this->setRole(BAN);
            else
                return;

        }
        else if (str.substr(0,9).compare("setunban:") == 0){
            if (str.substr(9, str.length()).compare(this->getName()) == 0)
                this->setRole(MEM);
            else
                return;
        }
        else if (str.substr(0,1).compare("@") == 0){
            int sendPos = str.find(':');
            string send_name = str.substr(1, sendPos - 1);
            int recPos = str.find(' ');
            string rec_name = str.substr(sendPos + 1, (recPos - 1) - sendPos);
            string key = str.substr(recPos + 1, str.length() - recPos - 1);
            if (rec_name.compare(this->getName()) == 0)
                cout << FileHandle::getCurrentTime() << "  @private " << send_name << ": " << key << endl;
            else{
                return;
            }
        }
        else {
            cout << str << endl;
        }








    }
}

//MARK:- close socket
void Client::finish()
{
    closesocket(serverSocket);
    WSACleanup();
}
//MARK:- getters
string Client::getName()
{
    return this->name;
}

string Client::getRoomId()
{
    return this->roomId;
}
Status Client::getStatus()
{
    return this->status;
}
Member Client::getRole()
{
    return this->role;
}

char* stringToCharArray(string str){
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}

void Client::showName(){
    cout << "Yours nick name: "<< this->name << endl;
}

void Client::setName(string name){
    this->name = name;
}

void Client::setRole(Member role){
    this->role = role;
}
