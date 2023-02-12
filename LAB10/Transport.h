#pragma once
#include "Utilities.h"

class Transport
{
public:
	char* code;
	char* departure;
	char* arrival;
	Date date;
	int total_seat;
	int booked_seat;
public:
	Transport();
	Transport(const char*, const char*, const char*, const Date, const int, const int);
	Transport(const char*, const char*, const char*, const char*, const int, const int);
	Transport(const Transport&);
	Transport(string, const char);
	virtual ~Transport();
	char* getCode();
	char* getDeparture();
	char* getArrival();
	Date getDate();
	int getTotal_seat();
	int getBooked_seat();
	void setCode(const char*);
	void setDeparture(const char*);
	void setArrival(const char*);
	void setDate(const Date);
	void setTotal_seat(const int);
	void setBooked_seat(const int);
	bool operator==(Transport&);
	virtual Transport* clone();
	virtual string toString();
	virtual string toStringFile(const char);
	virtual string className();
	virtual Transport* pointer();
};

const Transport def("0,0,0,0/0/0,0,0,0",',');