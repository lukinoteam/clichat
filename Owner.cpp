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
	ofstream myfile;
	//enter the directory file
	myfile.open("", ios::app);
	if (myfile.is_open()) {
		myfile << user << endl;
		myfile.close();
	}
}
void Owner::mod(string user) {
	ofstream myfile;
	//enter the directory file
	myfile.open("",ios::app);
	if (myfile.is_open()) {
		myfile << user << endl;
		myfile.close();
	}

}
void Owner::unMod(string user) {
	//read a file
	ifstream readFile;
	//write into a temp file(just rewrite the mod list with some conditions)
	ofstream tempFile;
	//directory of mod list
	readFile.open("");
	//directory of temp list
	tempFile.open("");
	if (readFile.is_open()) {
		string line = "";
		while (getline(readFile, line)) {
			if (line != user) {
				tempFile << line << endl;
			}
		}
		tempFile.close();
		readFile.close();
	}
	//rewrite the list and remove temp list
	readFile.open("");
	tempFile.open("");
	if (readFile.is_open()) {
		string line = "";
		while (getline(readFile, line)) {
			tempFile << line << endl;
		}
		tempFile.close();
		readFile.close();
	}
	remove("");
}
void Owner::unBanUser(string user) {
	//read a file
	ifstream readFile;
	//write into a temp file(just rewrite the mod list with some conditions)
	ofstream tempFile;
	//directory of mod list
	readFile.open("");
	//directory of temp list
	tempFile.open("");
	if (readFile.is_open()) {
		string line = "";
		while (getline(readFile, line)) {
			if (line != user) {
				tempFile << line << endl;
			}
		}
		tempFile.close();
		readFile.close();
	}
	//rewrite the list and remove temp list
	readFile.open("");
	tempFile.open("");
	if (readFile.is_open()) {
		string line = "";
		while (getline(readFile, line)) {
			tempFile << line << endl;
		}
		tempFile.close();
		readFile.close();
	}
	remove("");
}
