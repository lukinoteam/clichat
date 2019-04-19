#include "Config.h"

#include <iostream>
#include <string>
#include <vector>
#include "Owner.h"


using namespace std;

Config::Config(string id)
{
    room_id = id;
}

Config::~Config()
{
    //dtor
}

Owner Config::getOwner() {
    return owner;
}
void Config::setOwner(Owner o) {
    owner = o;
}
string Config::getIP() {
    return ip;
}
void Config::setIP(string str) {
    ip = str;
}
int Config::getPort() {
    return port;
}
void Config::setPort(int n) {
    port = n;
}
string Config::getName() {
    return name;
}
void Config::setName(string str) {
    name = str;
}
vector<string> Config::getFilterList() {
    return filter_list;
}
void Config::setFilterList(vector<string> v) {
    filter_list = v;
}
vector<string> Config::getBanList() {
    return ban_list;
}
void Config::setBanList(vector<string> v) {
    ban_list = v;
}
vector<string> Config::getModList() {
    return mod_list;
}
void Config::setModList(vector<string> v) {
    mod_list = v;
}
vector<string> Config::getMemberList() {
    return member_list;
}
void Config::setMemberList(vector<string> v) {
    member_list = v;
}
