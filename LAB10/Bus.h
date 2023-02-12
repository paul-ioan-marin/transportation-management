#pragma once
#include "Transport.h"

class Bus :public Transport
{
private:
	int time;
public:
	Bus();
	Bus(const char*, const char*, const char*, const Date, const int, const int, const int);
	Bus(const char*, const char*, const char*, const char*, const int, const int, const int);
	Bus(const Bus&);
	Bus(string, const char);
	~Bus();
	int getTime();
	void setTime(const int);
	Transport* clone();
	string toString();
	string toStringFile(const char);
	string className();
	Transport* pointer();
};

