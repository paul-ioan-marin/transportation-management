#pragma once
#include "Service.h"

class Customer
{
public:
	vector<Transport*> search(Service&, const Date&);
	void book(Service&, const char*, int);
};