#include "stdafx.h"
#include "Owner.h"
Owner::Owner()
{
}


Owner::~Owner()
{
}
void Owner::setRoomId(string str)
{
	this->room_id = str;
}
string Owner::getRoomId() {
	return this->room_id;
}
void Owner::setInfo(string rules,string user) {

}
void Owner::banUser(string user) {

}
void Owner::mod(string user) {

}
void Owner::unMod(string user) {

}
