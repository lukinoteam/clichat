#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;
class FileHandle
{
public:
	FileHandle();
	~FileHandle();
	string replaceData(string content,string file_content,string file_replace);
	void addData(string content,string file);
	void removeData(string content,string file, char temp_file[100]);
	string showData(string file);
    string showFilterData(string keyFile, string repFile);

	int isExistData(string content, string file);
	static string getCurrentTime();
};
