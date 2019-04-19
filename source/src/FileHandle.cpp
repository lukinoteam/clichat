//#include "stdafx.h"
#include "FileHandle.h"


FileHandle::FileHandle()
{
}


FileHandle::~FileHandle()
{
}
string FileHandle::replaceData(string content,string file_content,string file_replace) {
	string word = "";
	ifstream fileContent;
	ifstream fileReplace;
	istringstream ss(content);
	string new_string = "";
	while (ss >> word) {
		fileContent.open(file_content);
		string temp = "";
		int line = 0;
		while (getline(fileContent, temp)) {
			line++;
			if (temp == word) {
				fileReplace.open(file_replace);
				string replace_string = "";
				for (int i = 1; i <= line; i++) {
					getline(fileReplace, replace_string);
				}
				word = replace_string;
				fileReplace.close();
				break;
			}
		}
		fileContent.close();
		new_string += word + " ";
		//delete the last space
	 }
	int length = new_string.size() - 1;
	new_string = new_string.substr(0, length);
	return new_string;

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
string FileHandle::showData(string file) {
	ifstream myfile;
	myfile.open(file);
	string result = "";
	string line;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			result += line + "\n";
		}
		myfile.close();
	}
	return result;
}

string FileHandle::showFilterData(string keyFile, string repFile){
    ifstream myfile;
	myfile.open(keyFile);
	string result = "";
	string line;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			result += line + "\t:\t" + replaceData(line, keyFile, repFile) + "\n";
		}
		myfile.close();
	}
	return result;
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
void FileHandle::removeData(string content, string file,char temp_file[100]) {
	//read a file
	ifstream readFile;
	//write into a temp file(just rewrite list without content lines)
	ofstream tempFile;
	//directory of list
	readFile.open(file);
	//directory of temp list
	tempFile.open(temp_file);
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
	readFile.open(temp_file);
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
	remove(temp_file);
}


string FileHandle::getCurrentTime(){
    string currentTime = "";

    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    currentTime += to_string(now->tm_hour);
    currentTime += ':';
    currentTime += to_string(now->tm_min);


    return currentTime;
}
