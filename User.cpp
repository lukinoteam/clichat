#include "stdafx.h"
#include "User.h"
#include <fstream>

User::User()
{
}
void User::leave() {

}
void User::info() {

}
void User::mods() {
	ifstream stream;
	//Directory of mod_list
	stream.open("");
	string name;
	cout << "List of mods : " << endl;
	if (stream.is_open()) {
		while (getline(stream, name)) {
			cout << name << endl;
		}
	}
}
void User::nickname() {

}
void User::setNickname(string str) {

}
string User::getIp() {
	return this->ip;
}
string User::getName(){
	return this->name;
}
string User::getRoom_id() {
	return this->room_id;
}
void User::setIp(string str) {
	this->ip = str;
}
void User::setName(string str) {
	this->name = str;
}
void User::setRoomId(string str) {
	this->room_id = str;
}
User::~User()
{
}
