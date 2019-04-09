#pragma once
#include <string>
using namespace std;
class Owner
{
public:
	Owner();
	~Owner();
	void setInfo(string rules, string user);
	void banUser(string user);
	void unBanUser(string user);
	void mod(string user);
	void unMod(string user);
	string getRoomId();
	void setRoomId(string str);
private:
	string room_id;
};

