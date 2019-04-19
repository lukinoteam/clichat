#include <string>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include "Enums.h"
#include <vector>
#include <process.h>
#include "Server.h"
#include "ClientHandler.h"
#include "Logger.h"
#include "FileHandle.h"

using namespace std;

void threadOnNewSocket(void *data);
char* stringToCharArray(string str);
int bufferHandle(string str, char* buffer, vector<SOCKET> clients, SOCKET clientSocket, void *data);

string CLIENT_LIST_PATH = "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/ClientList.txt";
string MOD_LIST_PATH = "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/ModList.txt";
string BAN_LIST_PATH = "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/BanList.txt";
string FILTER_KEY_PATH = "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/FilterKeywords.txt";
string FILTER_REP_PATH = "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/FilterReplaced.txt";
string TEMP_PATH = "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp.txt";


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

//Function to receive message from socket
int receiveMessage(char* buffer, SOCKET clientSocket){
    return recv(clientSocket, buffer, sizeof(&buffer) * 100, 0);
}

//Broadcast:
void broadcast(string currentTime, char* buffer, vector<SOCKET> clients){
    string temp(buffer);
    temp = currentTime + "  " + temp;
    buffer = stringToCharArray(temp);

    for (size_t i = 0; i < clients.size(); ++i)
    {
        send(clients[i], buffer, sizeof(&buffer) * strlen(buffer), 0);
    }
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

        int resultRev = receiveMessage(buffer, clientSocket);
        string str = buffer;


        int resultSend = bufferHandle(str, buffer, clients, clientSocket, data);
        if (resultSend == 1){
            continue;
        }
        if (resultSend == 2){
            return;
        }

        if (resultRev == -1){
            string notice = "A member has disconnected!";
            broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);
            return;
        }

        int namePos = str.find(':');
        string key = str.substr(namePos + 2, str.length());
        FileHandle* fileHandle = new FileHandle();
        if (fileHandle->isExistData(key, FILTER_KEY_PATH) == 1){
            string data = fileHandle->replaceData(key, FILTER_KEY_PATH, FILTER_REP_PATH);
            string message = str.substr(0, namePos) + ": " + data;
            broadcast(FileHandle::getCurrentTime(), stringToCharArray(message), clients);
            continue;
        }

        broadcast(FileHandle::getCurrentTime(), buffer, clients);
        //Reset char array
        memset(buffer, 0, sizeof(buffer));
    }
}

// Handle buffer from client
int bufferHandle(string str, char* buffer, vector<SOCKET> clients, SOCKET clientSocket, void *data){

    Logger* logger;
    FileHandle* fileHandle = new FileHandle();

    // Log message to chat.log
    logger->logMessage(str);

    // Handle new client join Server
    if (str.substr(0,11).compare("client_join") == 0){
        string clientRole = str.substr(12, 3);
        string clientName = str.substr(16, str.length());

        if (fileHandle->isExistData(clientName, BAN_LIST_PATH) == 1){

        }
        fileHandle->addData(clientRole + ":" + clientName, CLIENT_LIST_PATH);

        string notice = clientName + " have joined.";

        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Client leave server
    if (str.substr(0,11).compare("client_exit") == 0){
        string notice = str.substr(12, str.length()) + " have left.";
        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);
        memset(buffer, 0, sizeof(buffer));
        return 2;
    }

    // Handle: Set new nick name for client
    if (str.substr(0, 13).compare("current_name:") == 0){
        string currentName = str.substr(13, str.length());

        memset(buffer, 0, sizeof(buffer));
        receiveMessage(buffer, clientSocket);
        string str = buffer;

        string changeName = str.substr(12, str.length());

        string notice = currentName + " changed name to " + changeName;

        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Ban client
    if (str.substr(0, 9).compare("ban_name:") == 0){
        string banName = str.substr(9, str.length());
        string notice = banName + " has been banned!";
        fileHandle->addData("BAN:" + banName, CLIENT_LIST_PATH);
        fileHandle->addData(banName, BAN_LIST_PATH);
        fileHandle->removeData("MEM:" + banName, CLIENT_LIST_PATH , stringToCharArray(TEMP_PATH));
        fileHandle->removeData("MOD:" + banName, CLIENT_LIST_PATH , stringToCharArray(TEMP_PATH));

        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);
        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray("setban:" + banName);
        for (size_t i = 0; i < clients.size(); ++i)
        {
            send(clients[i], buffer, sizeof(&buffer) * strlen(buffer), 0);
        }
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Unban Client
    if (str.substr(0, 11).compare("unban_name:") == 0){
        string unbanName = str.substr(11, str.length());
        string notice = unbanName + " has been unbanned!";
        fileHandle->removeData("BAN:" + unbanName, CLIENT_LIST_PATH , stringToCharArray(TEMP_PATH));
        fileHandle->addData("MEM:" + unbanName, CLIENT_LIST_PATH);
        fileHandle->removeData(unbanName, BAN_LIST_PATH , stringToCharArray(TEMP_PATH));

        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);
        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray("setunban:" + unbanName);
        for (size_t i = 0; i < clients.size(); ++i)
        {
            send(clients[i], buffer, sizeof(&buffer) * strlen(buffer), 0);
        }
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Set mod to client
    if (str.substr(0, 9).compare("mod_name:") == 0){
        string modName = str.substr(9, str.length());
        string notice = modName + " has been set to mod!";

        fileHandle->addData("MOD:" + modName, CLIENT_LIST_PATH);
        fileHandle->removeData("MEM:" + modName, CLIENT_LIST_PATH , stringToCharArray(TEMP_PATH));
        fileHandle->addData(modName, MOD_LIST_PATH);

        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);
        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray("setmod:" + modName);
        for (size_t i = 0; i < clients.size(); ++i)
        {
            send(clients[i], buffer, sizeof(&buffer) * strlen(buffer), 0);
        }
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Set unmod to client
    if (str.substr(0, 11).compare("unmod_name:") == 0){
        string unmodName = str.substr(11, str.length());
        string notice = unmodName + " has been set to member!";

        fileHandle->addData("MEM:" + unmodName, CLIENT_LIST_PATH);
        fileHandle->removeData("MOD:" + unmodName, CLIENT_LIST_PATH , stringToCharArray(TEMP_PATH));
        fileHandle->removeData(unmodName, MOD_LIST_PATH, stringToCharArray(TEMP_PATH));

        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);
        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray("setunmod:" + unmodName);
        for (size_t i = 0; i < clients.size(); ++i)
        {
            send(clients[i], buffer, sizeof(&buffer) * strlen(buffer), 0);
        }
        memset(buffer, 0, sizeof(buffer));

        return 1;
    }

    // Handle: Client request info
    if (str.substr(0, 9).compare("get_info:") == 0){
        ClientHandler *handler = (ClientHandler *)data;
        Server *server = handler->getServer();
        string roomInfo = "send_info:" + server->getRoom()->getRoomInfo();
        delete handler;
        delete server;

        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray(roomInfo);
        send(clientSocket, buffer, sizeof(&buffer) * strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Client request mods list
    if (str.substr(0, 9).compare("get_mods:") == 0){
        string mods = "send_mods:\n" + fileHandle->showData(MOD_LIST_PATH);
        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray(mods);
        send(clientSocket, buffer, sizeof(&buffer) * strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }


    // Handle: Admin change Room info
    if (str.substr(0, 11).compare("edit_owner:") == 0){
        string editOwner = str.substr(11, str.length());

        memset(buffer, 0, sizeof(buffer));
        receiveMessage(buffer, clientSocket);
        string str = buffer;
        string editRule = str.substr(10, str.length());

        ClientHandler *handler = (ClientHandler *)data;
        Server *server = handler->getServer();
        vector<SOCKET> clients = server->getClients();

        server->getRoom()->setOwner(editOwner);
        server->getRoom()->setRule(editRule);


        string notice = "- ROOM INFO CHANGED --";
        broadcast("-", stringToCharArray(notice), clients);
        notice = "Owner: " + editOwner + "\tRule: " + editRule;
        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);

        delete handler;
        delete server;

        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Add filter keyword
    if (str.substr(0, 11).compare("filter_key:") == 0){
        string filterKey = str.substr(11, str.length());

        memset(buffer, 0, sizeof(buffer));
        receiveMessage(buffer, clientSocket);
        string str = buffer;

        string filterRep = str.substr(11, str.length());

        fileHandle->addData(filterKey, FILTER_KEY_PATH);
        fileHandle->addData(filterRep, FILTER_REP_PATH);


        string notice = "Added filter keyword: " + filterKey + " : " + filterRep;
        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);

        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Remove filter keyword
    if (str.substr(0, 13).compare("unfilter_key:") == 0){
        string filterKey = str.substr(13, str.length());
        string replaceKey = fileHandle->replaceData(filterKey, FILTER_KEY_PATH, FILTER_REP_PATH);

        fileHandle->removeData(filterKey, FILTER_KEY_PATH, stringToCharArray(TEMP_PATH));
        fileHandle->removeData(replaceKey, FILTER_REP_PATH, stringToCharArray(TEMP_PATH));

        string notice = "Remove filter keyword: " + filterKey + " : " + replaceKey;
        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);

        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Client request filter keywords list
    if (str.substr(0, 12).compare("get_filters:") == 0){
        string filters = "send_filters:\n" + fileHandle->showFilterData(FILTER_KEY_PATH, FILTER_REP_PATH);
        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray(filters);
        send(clientSocket, buffer, sizeof(&buffer) * strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }
    // Handle: Client request member list
    if (str.substr(0, 11).compare("get_report:") == 0){
        string report = "send_report:\n" + fileHandle->showData(CLIENT_LIST_PATH);
        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray(report);
        send(clientSocket, buffer, sizeof(&buffer) * strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    if (str.substr(0, 1).compare("@") == 0){
        int sendPos = str.find(':');
        string send_name = str.substr(1, sendPos - 1);
        int recPos = str.find(' ');
        string rec_name = str.substr(sendPos + 1, (recPos - 1) - sendPos);
        string key = str.substr(recPos + 1, str.length() - recPos - 1);

        string message = "@" + send_name + ":" + rec_name + " " + key;
        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray(message);
        for (size_t i = 0; i < clients.size(); ++i)
        {
            send(clients[i], buffer, sizeof(&buffer) * strlen(buffer), 0);
        }
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }
}


