#pragma once
#include "Utilities.h"

class User
{
private:
	char* name;
	char* password;
public:
	User();
	User(const char*, const char*);
	User(const User&);
	User(string, const char);
	~User();
	char* getName();
	char* getPassword();
	void setName(const char*);
	void setPassword(const char*);
	bool operator==(const User&);
	User* clone();
	string toString();
	string toStringFile(const char);
	string className();
};