#include <iostream>
#include <string>
#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include "Server.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Server * server = Server::getInstance();
    server->start();
    server->run();
    return 0;
}
