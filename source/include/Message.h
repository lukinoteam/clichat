#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using namespace std;

class Message
{
    public:
        Message(string i);
        virtual ~Message();
        void setTime(string t);
        string getTime();
        void setSendUser(string u);
        string getSendUser();
        void setReceiveRoom(string r);
        string getReceiveRoom();
        void setContent(string c);
        string getContent();

    private:
        string id;
        string time;
        string sendUser;
        string receiveRoom;
        string content;
};

#endif // MESSAGE_H
