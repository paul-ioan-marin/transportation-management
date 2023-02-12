#include "Plane.h"

Plane::Plane():Transport()
{
	transit = NULL;
}

Plane::Plane(const char* newC, const char* newDep,
	const char* newArr, const Date newD,
	const char* newTr, const int newT, const int newB)
	:Transport(newC, newDep, newArr, newD, newT, newB)
{
	if (strcmp("da", newTr) != 0 && strcmp("nu", newTr) != 0)
		throw TransportCreateException("Ati introdus gresit campul escala!");
	setTransit(newTr);
}

Plane::Plane(const char* newC, const char* newDep,
	const char* newArr, const char* newD,
	const char* newTr, const int newT, const int newB)
	: Transport(newC, newDep, newArr, newD, newT, newB)
{
	if (strcmp("da", newTr) != 0 && strcmp("nu", newTr) != 0)
		throw TransportCreateException("Ati introdus gresit campul escala!");
	setTransit(newTr);
}

Plane::Plane(const Plane& p) : Transport(p)
{
	setTransit(p.transit);
}

Plane::Plane(string line, const char del)
{
	vector<string> tokens = readLine(line, del);
	if (tokens[4] != "da" && tokens[4] != "nu")
		throw TransportCreateException("Ati introdus gresit campul escala!");
	setCode(tokens[0].c_str());
	setDeparture(tokens[1].c_str());
	setArrival(tokens[2].c_str());
	setDate(date_str(tokens[3]));
	setTransit(tokens[4].c_str());
	setTotal_seat(stoi(tokens[5]));
	setBooked_seat(stoi(tokens[6]));
}

Plane::~Plane()
{
	if (transit)
		delete[] transit;
}

char* Plane::getTransit() { return transit; }

void Plane::setTransit(const char* newTr)
{
	if (strcmp("da", newTr) != 0 && strcmp("nu", newTr) != 0)
		throw TransportCreateException("Ati introdus gresit campul escala!");
	transit = new char[strlen(newTr) + 1];
	strcpy_s(transit, strlen(newTr) + 1, newTr);
}

Transport* Plane::clone()
{
	Transport* crt = new Plane(*this);
	return crt;
}

string Plane::toString()
{
	string s_code(code);
	string s_departure(departure);
	string s_arrival(arrival);
	string s_transit(transit);
	return "Cod: " + s_code + " Locatie plecare: " + s_departure
		+ " Locatie sosire: " + s_arrival + " Data plecare: " +
		to_string(date) + " Escala: " + s_transit + " Total locuri: "
		+ to_string(total_seat) + " Locuri rezervate: " + to_string(booked_seat);
}

string Plane::toStringFile(const char del)
{
	string s_code(code);
	string s_departure(departure);
	string s_arrival(arrival);
	string s_transit(transit);
	return s_code + del + s_departure + del + s_arrival + del + to_string(date)
		+ del + s_transit + del + to_string(total_seat) + del + to_string(booked_seat);
}

string Plane::className()
{
	return "Plane";
}

Transport* Plane::pointer()
{
	return (Plane*)this;
}