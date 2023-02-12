#include "Transport.h"

Transport::Transport()
{
	code = NULL;
	departure = NULL;
	arrival = NULL;
	total_seat = 0;
	booked_seat = 0;
}

Transport::Transport(const char* newC, const char* newDep,
	const char* newArr, const Date newD, const int newT, const int newB)
{
	if (newT <= 0)
		throw TransportCreateException("Numarul total de locuri trebuie sa fie pozitiv!");
	if (newB <= 0)
		throw TransportCreateException("Numarul de locuri rezervate trebuie sa fie pozitiv!");
	if (newT < newB)
		throw TransportCreateException("Numarul total de locuri trebuie sa fie mai mare decat numarul de locuri rezervate!");
	setCode(newC);
	setDeparture(newDep);
	setArrival(newArr);
	setDate(newD);
	setTotal_seat(newT);
	setBooked_seat(newB);
}

Transport::Transport(const char* newC, const char* newDep,
	const char* newArr, const char* newD, const int newT, const int newB)
{
	if (newT <= 0)
		throw TransportCreateException("Numarul total de locuri trebuie sa fie pozitiv!");
	if (newB <= 0)
		throw TransportCreateException("Numarul de locuri rezervate trebuie sa fie pozitiv!");
	if (newT < newB)
		throw TransportCreateException("Numarul total de locuri trebuie sa fie mai mare decat numarul de locuri rezervate!");
	setCode(newC);
	setDeparture(newDep);
	setArrival(newArr);
	string str(newD);
	setDate(date_str(str));
	setTotal_seat(newT);
	setBooked_seat(newB);
}

Transport::Transport(const Transport& t)
{
	setCode(t.code);
	setDeparture(t.departure);
	setArrival(t.arrival);
	setDate(t.date);
	setTotal_seat(t.total_seat);
	setBooked_seat(t.booked_seat);
}

Transport::Transport(string s, const char del)
{
	code = NULL;
	departure = NULL;
	arrival = NULL;
	total_seat = 0;
	booked_seat = 0;
}

Transport::~Transport()
{
	if (code)
		delete[] code;
	if (departure)
		delete[] departure;
	if (arrival)
		delete[] arrival;
}

char* Transport::getCode() { return code; }
char* Transport::getDeparture() { return departure; }
char* Transport::getArrival() { return arrival; }
Date Transport::getDate() { return date; }
int Transport::getTotal_seat() { return total_seat; }
int Transport::getBooked_seat() { return booked_seat; }

void Transport::setCode(const char* newCode)
{
	code = new char[strlen(newCode) + 1];
	strcpy_s(code, strlen(newCode) + 1, newCode);
}

void Transport::setDeparture(const char* newDeparture)
{
	departure = new char[strlen(newDeparture) + 1];
	strcpy_s(departure, strlen(newDeparture) + 1, newDeparture);
}

void Transport::setArrival(const char* newArrival)
{
	arrival = new char[strlen(newArrival) + 1];
	strcpy_s(arrival, strlen(newArrival) + 1, newArrival);
}

void Transport::setDate(const Date newD)
{
	date.day = newD.day;
	date.month = newD.month;
	date.year = newD.year;
}

void Transport::setTotal_seat(const int newT)
{
	if (newT <= 0)
		throw TransportCreateException("Numarul total de locuri trebuie sa fie pozitiv!");
	if(newT < this->booked_seat)
		throw TransportCreateException("Numarul total de locuri trebuie sa fie mai mare decat numarul de locuri rezervate!");
	total_seat = newT;
}

void Transport::setBooked_seat(const int newB)
{
	if (newB <= 0)
		throw TransportCreateException("Numarul de locuri rezervate trebuie sa fie pozitiv!");
	if (newB > this->total_seat)
		throw TransportCreateException("Numarul total de locuri trebuie sa fie mai mare decat numarul de locuri rezervate!");
	booked_seat = newB;
}

bool Transport::operator==(Transport& t)
{
	Transport* aux = t.pointer();
	return (this->toString() == aux->toString());
}

Transport* Transport::clone()
{
	return new Transport(*this);
}

string Transport::toString()
{
	return "<toString>";
}

string Transport::toStringFile(const char del)
{
	return "<toStringFile>";
}

string Transport::className()
{
	return "Transport";
}

Transport* Transport::pointer()
{
	return this;
}