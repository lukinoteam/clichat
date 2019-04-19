#include "Owner.h"

Owner::Owner()
{
    //ctor
}

Owner::~Owner()
{
    //dtor
}

string Owner::getRoomId() {
    return room_id;
}
void Owner::setRoomId(string str) {
    room_id = str;
}
