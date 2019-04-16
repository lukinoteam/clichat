#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
class FileHandle
{
public:
	FileHandle();
	~FileHandle();
	//ham test , voi string content se hien ra mot string moi voi noi dung thay doi
	void replace(string content,string file_content,string file_replace);
	//add data cho filter
	void addFilterData(string content, string replace, string file_content,string file_replace);
	void addData(string content,string file);
	void removeData(string content,string file,char temp_file[100] );
	void showData(string file);
	int isExistData(string content, string file);
};

