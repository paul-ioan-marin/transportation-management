#include "Bus.h"

Bus::Bus() :Transport()
{
	time = 0;
}

Bus::Bus(const char* newC, const char* newDep,
	const char* newArr, const Date newD,
	const int newTi, const int newT, const int newB)
	: Transport(newC, newDep, newArr, newD, newT, newB)
{
	if (newTi <= 0)
		throw TransportCreateException("Durata trebuie sa fie un numar pozitiv!");
	setTime(newTi);
}

Bus::Bus(const char* newC, const char* newDep,
	const char* newArr, const char* newD,
	const int newTi, const int newT, const int newB)
	: Transport(newC, newDep, newArr, newD, newT, newB)
{
	if (newTi <= 0)
		throw TransportCreateException("Durata trebuie sa fie un numar pozitiv!");
	setTime(newTi);
}

Bus::Bus(const Bus& p) : Transport(p)
{
	setTime(p.time);
}

Bus::Bus(string line, const char del)
{
	vector<string> tokens = readLine(line, del);
	if (stoi(tokens[4]) <= 0)
		throw TransportCreateException("Durata trebuie sa fie un numar pozitiv!");
	setCode(tokens[0].c_str());
	setDeparture(tokens[1].c_str());
	setArrival(tokens[2].c_str());
	setDate(date_str(tokens[3]));
	setTime(stoi(tokens[4]));
	setTotal_seat(stoi(tokens[5]));
	setBooked_seat(stoi(tokens[6]));
}

Bus::~Bus() {}

int Bus::getTime() { return time; }

void Bus::setTime(const int newT)
{
	if (newT <= 0)
		throw TransportCreateException("Durata trebuie sa fie un numar pozitiv!");
	time = newT;
}

Transport* Bus::clone()
{
	Transport* crt = new Bus(*this);
	return crt;
}

string Bus::toString()
{
	string s_code(code);
	string s_departure(departure);
	string s_arrival(arrival);
	return "Cod: " + s_code + " Locatie plecare: " + s_departure
		+ " Locatie sosire: " + s_arrival + " Data plecare: " +
		to_string(date) + " Durata calatorie: " + to_string(time) + " Total locuri: "
		+ to_string(total_seat) + " Locuri rezervate: " + to_string(booked_seat);
}

string Bus::toStringFile(const char del)
{
	string s_code(code);
	string s_departure(departure);
	string s_arrival(arrival);
	return s_code + del + s_departure + del + s_arrival + del + to_string(date)
		+ del + to_string(time) + del + to_string(total_seat) + del + to_string(booked_seat);
}

string Bus::className()
{
	return "Bus";
}

Transport* Bus::pointer()
{
	return (Bus*)this;
}