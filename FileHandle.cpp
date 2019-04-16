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
void FileHandle::replace(string content,string file_content,string file_replace) {
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
	cout << new_string;

} 
void FileHandle::addFilterData(string content, string replace, string file_content, string file_replace) {
	ofstream fileContent;
	ofstream fileReplace;
	fileContent.open(file_content, ios::app);
	fileReplace.open(file_replace, ios::app);
	if (fileContent.is_open() && fileReplace.is_open()) {
		fileContent << content << endl;
		fileReplace << replace << endl;
		fileContent.close();
		fileReplace.close();
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
			myfile.close();
			return 1;
		}
	}
	myfile.close();
	return -1;
}
//temp_file is directory of temp file
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

