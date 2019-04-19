#include "Message.h"

Message::Message(string i)
{
    id = i;
}

Message::~Message()
{
    //dtor
}

void Message::setTime(string t){
    time = t;
}
string Message::getTime(){
    return time;
}
void Message::setSendUser(string u){
    sendUser = u;
}
string Message::getSendUser(){
    return sendUser;
}
void Message::setReceiveRoom(string r){
    receiveRoom = r;
}
string Message::getReceiveRoom(){
    return receiveRoom;
}
void Message::setContent(string c){
    content = c;
}
string Message::getContent(){
    return content;
}
