#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class FileHandle
{
public:
	FileHandle();
	~FileHandle();
	void addData(string content,string file);
	void removeData(string content,string file);
	void showData(string file);
	int isExistData(string content, string file);
};

