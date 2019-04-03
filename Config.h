#include <string>
#include <vector>
#include "Owner.h"
using namespace std;
class Config
{
public:
	Config() {

	}
	Owner getOwner() {
		return owner;
	}
	void setOwner(Owner o) {
		owner = o;
	}
	string getIP() {
		return ip;
	}
	void setIP(string str) {
		ip = str;
	}
	int getPort() {
		return port;
	}
	void setPort(int n) {
		port = n;
	}
	string getName() {
		return name;
	}
	void setName(string str) {
		name = str;
	}
	vector<string> getFilterList() {
		return filter_list;
	}
	void setFilterList(vector<string> v) {
		filter_list = v;
	}
	vector<string> getBanList() {
		return ban_list;
	}
	void setBanList(vector<string> v) {
		ban_list = v;
	}
	vector<string> getModList() {
		return mod_list;
	}
	void setModList(vector<string> v) {
		mod_list = v;
	}
	vector<string> getMemberList() {
		return member_list;
	}
	void setMemberList(vector<string> v) {
		member_list = v;
	}
private:
	string room_id;
	string name;
	string ip;
	int port;
	vector<string>filter_list;
	vector<string>ban_list;
	vector<string>mod_list;
	vector<string>member_list;
	Owner owner;
};

