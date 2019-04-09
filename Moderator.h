#pragma once
#include "User.h"
#include <string>
using namespace std;
class Moderator: public User
{
public:
	Moderator();
	~Moderator();
	void report();
	void filter();
	void filter(string word);
	void unFilter(string word);
	void privateMessage();
};

