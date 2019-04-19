#ifndef OWNER_H
#define OWNER_H

#include <string>

using namespace std;

class Owner
{
    public:
        Owner();
        virtual ~Owner();
        string getRoomId();
        void setRoomId(string str);
    private:
        string room_id;
};

#endif // OWNER_H
