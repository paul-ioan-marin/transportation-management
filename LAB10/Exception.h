#pragma once
#include <iostream>
#include <exception>

using namespace std;

class TransportCreateException : public exception
{
private:
	char* msg;
public:
	TransportCreateException(const char* m)
	{
		msg = new char[strlen(m) + 1];
		strcpy_s(msg, strlen(m) + 1, m);
	}
	virtual const char* what() const throw() { return msg; }
	~TransportCreateException() { if (msg) delete[] msg; }
};

class ExistingException : public exception
{
private:
	char* msg;
public:
	ExistingException(const char* m)
	{
		msg = new char[strlen(m) + 1];
		strcpy_s(msg, strlen(m) + 1, m);
	}
	virtual const char* what() const throw() { return msg; }
	~ExistingException() { if (msg) delete[] msg; }
};

class CodeNameException : public exception
{
private:
	char* msg;
public:
	CodeNameException(const char* m)
	{
		msg = new char[strlen(m) + 1];
		strcpy_s(msg, strlen(m) + 1, m);
	}
	virtual const char* what() const throw() { return msg; }
	~CodeNameException() { if (msg) delete[] msg; }
};

class CommandException : public exception
{
private:
	char* msg;
public:
	CommandException(const char* m)
	{
		msg = new char[strlen(m) + 1];
		strcpy_s(msg, strlen(m) + 1, m);
	}
	CommandException(const string m)
	{
		msg = new char[strlen(m.c_str()) + 1];
		strcpy_s(msg, strlen(m.c_str()) + 1, m.c_str());
	}
	virtual const char* what() const throw() { return msg; }
	~CommandException() { if (msg) delete[] msg; }
};

class InputException : public exception
{
private:
	char* msg;
public:
	InputException(const char* m)
	{
		msg = new char[strlen(m) + 1];
		strcpy_s(msg, strlen(m) + 1, m);
	}
	virtual const char* what() const throw() { return msg; }
	~InputException() { if (msg) delete[] msg; }
};