#include "User.h"

User::User()
{
	name = NULL;
	password = NULL;
}

User::User(const char* newU, const char* newP)
{
	setName(newU);
	setPassword(newP);
}

User::User(const User& u)
{
	setName(u.name);
	setPassword(u.password);
}

User::User(string line, const char del)
{
	vector<string> tokens = readLine(line, del);
	setName(tokens[0].c_str());
	setPassword(tokens[1].c_str());
}

User::~User()
{
	if (name)
		delete[] name;
	if (password)
		delete[] password;
}

char* User::getName() { return name; }
char* User::getPassword() { return password; }

void User::setName(const char* newN)
{
	name = new char[strlen(newN) + 1];
	strcpy_s(name, strlen(newN) + 1, newN);
}

void User::setPassword(const char* newP)
{
	password = new char[strlen(newP) + 1];
	strcpy_s(password, strlen(newP) + 1, newP);
}

bool User::operator==(const User& u)
{
	return (strcmp(name, u.name) == 0);
}

User* User::clone()
{
	User* ent = new User(*this);
	return new User(*this);
}

string User::toString()
{
	string s_name(name);
	string s_password(password);
	return "Nume: " + s_name + " Parola: " + s_password;
}

string User::toStringFile(const char del)
{
	string s_name(name);
	string s_password(password);
	return s_name + del + s_password;
}

string User::className()
{
	return "User";
}