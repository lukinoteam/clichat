#include "Room.h"
#include <iostream>
#include <string>
#include <vector>


using namespace std;

string getCurrentTime();

Room::Room(string owner, string rule)
{
    this->owner = owner;
    this->rule = rule;
    this->timeCreate = getCurrentTime();
}

Room::Room(){

}

Room::~Room()
{
    //dtor
}

string Room::getIP() {
    return ip;
}
void Room::setIP(string str) {
    ip = str;
}
int Room::getPort() {
    return port;
}
void Room::setPort(int n) {
    port = n;
}
string Room::getOwner() {
    return owner;
}

string Room::getTimeCreate(){
    return timeCreate;
}

string Room::getRule(){
    return rule;
}

string getCurrentTime(){
    string currentTime = "";

    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    currentTime += to_string((now->tm_year + 1900));
    currentTime += '-';
    currentTime += to_string((now->tm_mon + 1));
    currentTime += '-';
    currentTime += to_string(now->tm_mday);
    currentTime += ' ';
    currentTime += to_string(now->tm_hour);
    currentTime += ':';
    currentTime += to_string(now->tm_min);
    currentTime += ':';
    currentTime += to_string(now->tm_sec);

    return currentTime;
}

string Room::getRoomInfo(){
    return "Owner: " + owner + "\tRule: " + rule + "\tTime create: " + this->getTimeCreate();
}

void Room::setOwner(string owner){
    this->owner = owner;
}

void Room::setRule(string rule){
    this->rule = rule;
}

