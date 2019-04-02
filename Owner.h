#pragma once
#include <string>
using namespace std;
class Owner
{
public:
	Owner() {

	}
	string getRoomId() {
		return room_id;
	}
	void setRoomId(string str) {
		room_id = str;
	}
private:
	string room_id;
};

