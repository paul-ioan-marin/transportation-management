#pragma once
#include "Bus.h"
#include "Plane.h"

class Validator
{
public:
	Validator() {}
	~Validator() {}
	template <class T> void validate(T*) {}
	template <> void validate<Transport>(Transport* t)
	{
		if (strcmp(t->getCode(), "") == 0)
			throw TransportCreateException("Codul nu poate fi gol!");
		if (strcmp(t->getDeparture(), "") == 0)
			throw TransportCreateException("Locatia plecarii nu poate fi goala!");
		if (strcmp(t->getArrival(), "") == 0)
			throw TransportCreateException("Locatia destinatiei nu poate fi goala!");
		for (int i = 0; t->getDeparture()[i] != '\0'; i++)
			if (!isalpha(t->getDeparture()[i]))
				throw TransportCreateException("Locatia plecarii nu poate contine cifre!");
		for (int i = 0; t->getArrival()[i] != '\0'; i++)
			if (!isalpha(t->getArrival()[i]))
				throw TransportCreateException("Locatia destinatiei nu poate contine cifre!");
		if (t->className() == "Plane")
		{
			Plane* p = (Plane*)t;
			if (strcmp(p->getTransit(), "da") != 0 && strcmp(p->getTransit(), "nu") != 0)
				throw TransportCreateException("Ati introdus gresit campul escala!");
		}
	}
};