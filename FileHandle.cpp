#include "stdafx.h"
#include "FileHandle.h"


FileHandle::FileHandle()
{
}


FileHandle::~FileHandle()
{
}

void FileHandle::addData(string content, string file) {
	ofstream myfile;
	//enter the directory file
	myfile.open(file, ios::app);
	if (myfile.is_open()) {
		myfile << content << endl;
		myfile.close();
	}
}
void FileHandle::showData(string file) {
	ifstream myfile;
	myfile.open(file);
	string line;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			cout << line << endl;
		}
		myfile.close();
	}
}
int FileHandle::isExistData(string content, string file) {
	ifstream myfile;
	myfile.open(file);
	string line;
	while (getline(myfile, line)) {
		if (line == content) {
			return 1;
		}
	}
	return -1;
}
void FileHandle::removeData(string content, string file) {
	//read a file
	ifstream readFile;
	//write into a temp file(just rewrite list without content lines)
	ofstream tempFile;
	//directory of list
	readFile.open(file);
	//directory of temp list
	tempFile.open("");
	if (readFile.is_open()) {
		string line = "";
		while (getline(readFile, line)) {
			if (line != content) {
				tempFile << line << endl;
			}
		}
		tempFile.close();
		readFile.close();
	}
	//rewrite the list and remove temp list
	//temp file directory
	readFile.open("");
	tempFile.open(file);
	if (readFile.is_open()) {
		string line = "";
		while (getline(readFile, line)) {
			tempFile << line << endl;
		}
		tempFile.close();
		readFile.close();
	}
	//remove the tempFile
	remove("");
}

