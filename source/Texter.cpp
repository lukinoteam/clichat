#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <string>

using namespace std;

mutex mtx;

class Texter {
public:
    void mainThread();
    void subThread();
    void listenMessage();
    int getStatus();
    void setStatus(int status);
    mutex getMutex();
private:
    int running = 1;
};

void Texter::setStatus(int status){
    running = status;
}

int Texter::getStatus(){
    return running;
}


void Texter::mainThread(){
    while (running == 1){
        thread listen(listenMessage, this);
        thread client(subThread, this);

        if (client.joinable())
            client.join();
        if (listen.joinable())
            listen.join();

    }
    cout << "Exit room" << endl;
}


void Texter::subThread(){
    while (running == 1){
        string message;
        mtx.lock();
        getline(cin, message);
        mtx.unlock();

        if (message.compare("exit") == 0){
            running = 0;
        }

        cout <<"Message: "<< message << endl;

    }

}

void Texter::listenMessage(){
    while (running == 1){
        cout << "Getting message ..." << endl;
        usleep(990000);
    }
}

int main()
{
    Texter texter;
    thread test(texter.mainThread, Texter());
    test.join();
    return 0;
}
