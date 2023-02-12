#pragma once
#include "Service.h"
#include "Customer.h"

class UI
{
private:
	Service service;
	void user();
	void transport();
	void client();
	void boss();
	void login(int);
	template <class T> void all();
public:
	UI();
	~UI();
	void show();
};