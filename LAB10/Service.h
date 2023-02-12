#pragma once
#include "RepoFileCSV.h"
#include "RepoFileTXT.h"

class Service
{
	friend class Customer;
private:
	IRepo<Transport>* transport;
	IRepo<User>* user;
public:
	Service();
	~Service();
	Service(const char*, const char*, const char*);
	Service(const char*);
	template <class T> void add(T*);
	template <class T> void del(T*);
	template <class T> void mod(T*, T*);
	template <class T> int size();
	template <class T> vector<T*>& all();
	template <class T> T* at(int);
	bool login(const char*, const char*);
	void csv_or_txt(const char*);
	User* find_by_name(const char*);
	Transport* find_by_code(const char*);
	void delete_t(Transport*);
	void empty();
			//Transport* find_by_code_and_arrival(const char*, const char*);
};