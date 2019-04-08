#include <iostream>
#include <string>
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Client.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Client *client = new Client("CLIENT", MEMBER);
    client->connectToServer("127.0.0.1");
    char gret[1024] = "Hello from clone";
    client->sendMessage(gret);
    return 0;
}
