#include <string>
#include <iostream>
#include "Enum.h"
#pragma once
using namespace std;
class User
{
public:
	User();
	~User();
	void leave();
	void info();
	void nickname();
	void setNickname(string str);
	void mods();
	void setName(string str);
	void setIp(string str);
	void setRoomId(string str);
	string getName();
	string getIp();
	string getRoom_id();

protected:
	string name;
	string ip;
	enum online_status;
	enum member_status;
	string room_id;
};

