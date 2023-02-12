#pragma once
#include "Transport.h"

class Plane: public Transport
{
private:
	char* transit;
public:
	Plane();
	Plane(const char*, const char*, const char*, const Date, const char*, const int, const int);
	Plane(const char*, const char*, const char*, const char*, const char*, const int, const int);
	Plane(const Plane&);
	Plane(string, const char);
	~Plane();
	char* getTransit();
	void setTransit(const char*);
	Transport* clone();
	string toString();
	string toStringFile(const char);
	string className();
	Transport* pointer();
};