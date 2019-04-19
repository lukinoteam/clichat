#include "Texter.h"

Texter::Texter(string name, Member role, string ip)
{
    // Connect to server
    client = new Client(name, role);
    client->connectToServer(ip);

    cout << "Connected to IP: " << ip << endl;

    string roleList[] = {"ADM", "MOD", "MEM", "BAN"};

    // Send client_name to server
    string client_name = "client_join:" + roleList[role] + ":" + name;
    char* cstr = new char[client_name.length() + 1];
    strcpy(cstr, client_name.c_str());
    client->sendMessage(cstr);

}


Texter::~Texter()
{

}

void Texter::setStatus(int status){
    joined = status;
}

int Texter::getStatus(){
    return joined;
}


void Texter::sendToServer(string message){
    char* cstr = new char[message.length() + 1];
    strcpy(cstr, message.c_str());

    int result = client->sendMessage(cstr);
    if (result == -1 && client->getRole() != ADM){
        cout << "Server has shut down!" << endl;
        joined = 0;
    }
}

// Thread: send message to server
void Texter::sendThread(){
    while (joined == 1){
        string message;
        getline(cin, message);

            // Fix weird bug
        if (message.compare("") == 0){
            continue;
        }
        if (client->getRole() == BAN){
            cout << "You have been banned." << endl;
            continue;
        }
        messageHandle(message);

    }
}

// Thread: receive message from server
void Texter::receiveThread(){
    while(joined == 1){
        client->receiveMessage();
    }
}

void Texter::messageHandle(string message){


    // Command handle
    if (message.substr(0,1).compare("/") == 0){
        string command = message.substr(1, message.length());
        // Input: exit => Handle: Exit room.
        if (command.compare("leave") == 0){
            string notice = "client_exit:" + client->getName();
            sendToServer(notice);
            joined = 0;
        }
        else if (command.compare("nickname") == 0){
            client->showName();
            return;
        }
        else if (command.substr(0,7).compare("setnick") == 0){
            string currentName = "current_name:" + client->getName();
            string changeName = "change_name:" + command.substr(8, command.length());
            sendToServer(currentName);
            sendToServer(changeName);
            client->setName(command.substr(8, command.length()));
        }
        else if (command.substr(0,3).compare("ban") == 0){
            if (client->getRole() !=  ADM){
                cout << "Invalid command. For admin only" << endl;
            }
            else {
                string banName = "ban_name:" + command.substr(4, command.length());
                sendToServer(banName);
            }
        }
        else if (command.substr(0,5).compare("unban") == 0){
            if (client->getRole() !=  ADM){
                cout << "Invalid command. For admin only" << endl;
            }
            else {
                string unbanName = "unban_name:" + command.substr(6, command.length());
                sendToServer(unbanName);
            }
        }

        else if (command.substr(0,4).compare("mods") == 0){
            sendToServer("get_mods:");
        }

        else if (command.substr(0,3).compare("mod") == 0){
            if (client->getRole() !=  ADM){
                cout << "Invalid command. For admin only" << endl;
            }
            else {
                string modName = "mod_name:" + command.substr(4, command.length());
                sendToServer(modName);
            }
        }
        else if (command.substr(0,5).compare("unmod") == 0){
            if (client->getRole() !=  ADM){
                cout << "Invalid command. For admin only" << endl;
            }
            else {
                string unmodName = "unmod_name:" + command.substr(6, command.length());
                sendToServer(unmodName);
            }

        }
        else if (command.substr(0,4).compare("info") == 0){
            sendToServer("get_info:");
        }

        else if (command.substr(0,7).compare("setinfo") == 0){
            if (client->getRole() !=  ADM){
                cout << "Invalid command. For admin only" << endl;
            }
            else {
                string editOwner;
                string editRule;

                cout << "Input new Owner: " << endl;
                getline(cin, editOwner);
                cout << "Input new rule: " << endl;
                getline(cin, editRule);

                sendToServer("edit_owner:" + editOwner);
                sendToServer("edit_rule:" + editRule);
            }

        }

        else if (command.substr(0,7).compare("filters") == 0){
            sendToServer("get_filters:");
        }


        else if (command.substr(0,6).compare("filter") == 0){
            if (client->getRole() ==  ADM || client->getRole() ==  MOD){
                string keyword;
                string replacedWord;
                cout << "Input keyword: " << endl;
                getline(cin, keyword);
                cout << "Input replaced word: " << endl;
                getline(cin, replacedWord);

                sendToServer("filter_key:" + keyword);
                sendToServer("filter_rep:" + replacedWord);
            }
            else {
                cout << "Invalid command. For admin and mod only" << endl;

            }

        }
        else if (command.substr(0,8).compare("unfilter") == 0){
            if (client->getRole() ==  ADM || client->getRole() ==  MOD){
                string unfilterKey = "unfilter_key:" + command.substr(9, command.length());
                sendToServer(unfilterKey);
            }
            else {
                cout << "Invalid command. For admin and mod only" << endl;
            }
        }

        else if (command.substr(0,6).compare("report") == 0){
            if (client->getRole() ==  ADM || client->getRole() ==  MOD){
                sendToServer("get_report:");

            }
            else {
                cout << "Invalid command. For admin and mod only" << endl;
            }
        }

        else {
            cout << "Command not found!" << endl;
        }
    }

    else if (message.substr(0,1).compare("@") == 0){
        sendToServer("@" + client->getName() + ":" + message.substr(1, message.length()));
    }

    else {
        // Input: Normal Message
        string client_name = client->getName();
        message = client_name + ": " + message;

        sendToServer(message);
    }

}


// Controller
void Texter::run(){
    joined = 1;
    while (joined == 1)
    {
        thread receive(receiveThread, this);
        thread send(sendThread, this);

        if (receive.joinable())
            receive.join();
        if (send.joinable())
            send.join();

        if (joined == 0){
            client->finish();
        }
    }
}


