#include "stdafx.h"
#include "Config.h"
#include <fstream>
Config::Config()
{
	//change the directory file
	this->member_list = readFileList("D:/CPP Project/CliChat/CliChat/MemberList.txt");
	this->ban_list = readFileList("D:/CPP Project/CliChat/CliChat/BanList.txt");
	this->filter_list = readFileList("D:/CPP Project/CliChat/CliChat/FilterList.txt");
	this->mod_list = readFileList("D:/CPP Project/CliChat/CliChat/ModList.txt");
}

Config::~Config()
{
}
string Config::getIP() {
	return this->ip;
}
void Config::setIP(string s){
	this->ip = s;
}
string Config::getName() {
	return this->name;
}
void Config::setName(string s) {
	this->name = s;
}
void Config::setPort(int n) {
	this->port = n;
}
int Config::getPort() {
	return this->port;
}
void Config::setOwner(Owner o) {
	this->owner = o;
}
Owner Config::getOwner() {
	return this->owner;
}
void Config::setBanList(vector<string> vec) {
	this->ban_list = vec;
}
vector<string> Config::getBanList() {
	return this->ban_list;
}
void Config::setFilterList(vector<string> vec) {
	this->filter_list = vec;
}
vector<string> Config::getFilterList() {
	return this->filter_list;
}
void Config::setModList(vector<string> vec) {
	this->mod_list = vec;
}
vector<string> Config::getModList() {
	return this->mod_list;
}
void Config::setMemberList(vector<string> vec) {
	this->member_list = vec;
}
vector<string> Config::getMemberList() {
	return this->member_list;
}
//function readMember,Ban,Mod,Filter File
vector<string>Config::readFileList(string str) {
	vector<string>list;
	ifstream stream;
	stream.open(str);
	string member;
	if (stream.is_open()) {
		while (getline(stream, member)) {
			list.push_back(member);
	}
		stream.close();
	}
	return list;
}