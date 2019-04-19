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
        if (fileHandle->isExistData(key, "FilterKeywords.txt") == 1){
            string data = fileHandle->replaceData(key, "FilterKeywords.txt", "FilterReplaced.txt");
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

        if (fileHandle->isExistData(clientName, "BanList.txt") == 1){

        }
        fileHandle->addData(clientRole + ":" + clientName, "ClientList.txt");

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
        fileHandle->addData("BAN:" + banName, "ClientList.txt");
        fileHandle->addData(banName, "BanList.txt");
        fileHandle->removeData("MEM:" + banName, "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/ClientList.txt" , "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp.txt");
        fileHandle->removeData("MOD:" + banName, "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/ClientList.txt" , "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp.txt");

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
        fileHandle->removeData("BAN:" + unbanName, "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/ClientList.txt" , "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp.txt");
        fileHandle->addData("MEM:" + unbanName, "ClientList.txt");
        fileHandle->removeData(unbanName, "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/BanList.txt" , "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp.txt");

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

        fileHandle->addData("MOD:" + modName, "ClientList.txt");
        fileHandle->removeData("MEM:" + modName, "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/ClientList.txt" , "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp.txt");
        fileHandle->addData(modName, "ModList.txt");

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

        fileHandle->addData("MEM:" + unmodName, "ClientList.txt");
        fileHandle->removeData("MOD:" + unmodName, "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/CLientList.txt" , "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp.txt");
        fileHandle->removeData(unmodName, "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/ModList.txt","C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp");

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
        string mods = "send_mods:\n" + fileHandle->showData("ModList.txt");
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

        fileHandle->addData(filterKey, "FilterKeywords.txt");
        fileHandle->addData(filterRep, "FilterReplaced.txt");


        string notice = "Added filter keyword: " + filterKey + " : " + filterRep;
        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);

        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Remove filter keyword
    if (str.substr(0, 13).compare("unfilter_key:") == 0){
        string filterKey = str.substr(13, str.length());
        string replaceKey = fileHandle->replaceData(filterKey, "FilterKeywords.txt", "FilterReplaced.txt");

        fileHandle->removeData(filterKey, "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/FilterKeywords.txt","C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp");
        fileHandle->removeData(replaceKey, "C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/FilterReplaced.txt","C:/Users/lukin/OneDrive/Documents/Cpp/Clichat/bin/Debug/temp");

        string notice = "Remove filter keyword: " + filterKey + " : " + replaceKey;
        broadcast(FileHandle::getCurrentTime(), stringToCharArray(notice), clients);

        memset(buffer, 0, sizeof(buffer));
        return 1;
    }

    // Handle: Client request filter keywords list
    if (str.substr(0, 12).compare("get_filters:") == 0){
        string filters = "send_filters:\n" + fileHandle->showFilterData("FilterKeywords.txt", "FilterReplaced.txt");
        memset(buffer, 0, sizeof(buffer));
        buffer = stringToCharArray(filters);
        send(clientSocket, buffer, sizeof(&buffer) * strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        return 1;
    }
    // Handle: Client request member list
    if (str.substr(0, 11).compare("get_report:") == 0){
        string report = "send_report:\n" + fileHandle->showData("ClientList.txt");
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


