#include "Service.h"

Service::Service() {}

Service::~Service() {}

Service::Service(const char* type)
{
	if (strcmp(type, "csv") == 0)
	{
		transport = new RepoFileCSV<Transport>("TRANSPORT.CSV");
		user = new RepoFileCSV<User>("USER.CSV");
		transport->loadFromFile();
		user->loadFromFile();
		return;
	}
	if (strcmp(type, "txt") == 0)
	{
		transport = new RepoFileTXT<Transport>("TRANSPORT.TXT");
		user = new RepoFileTXT<User>("USER.TXT");
		transport->loadFromFile();
		user->loadFromFile();
		return;
	}
	throw CodeNameException("Tip de fisier indisponibil!");
}

Service::Service(const char* type, const char* name1, const char* name2)
{
	if (strcmp(type, "csv") == 0)
	{
		transport = new RepoFileCSV<Transport>(name1);
		user = new RepoFileCSV<User>(name2);
		transport->loadFromFile();
		user->loadFromFile();
		return;
	}
	if (strcmp(type, "txt") == 0)
	{
		transport = new RepoFileTXT<Transport>(name1);
		user = new RepoFileTXT<User>(name2);
		transport->loadFromFile();
		user->loadFromFile();
		return;
	}
	throw CodeNameException("Tip de fisier indisponibil!");
}

template <class T> void Service::add(T* ent) {}

template <> void Service::add<User>(User* ent)
{
	user->add(ent);
	user->saveToFile();
}

template <> void Service::add<Transport>(Transport* ent)
{
	transport->add(ent);
	transport->saveToFile();
}

template <class T> void Service::del(T* ent) {}

template <> void Service::del<User>(User* ent)
{
	user->del(ent);
	user->saveToFile();
}

template <> void Service::del<Transport>(Transport* ent)
{
	transport->del(ent);
	transport->saveToFile();
}

template <class T> void Service::mod(T* oldE, T* newE) {}

template <> void Service::mod<User>(User* oldE, User* newE)
{
	user->mod(oldE, newE);
	user->saveToFile();
}

template <> void Service::mod<Transport>(Transport* oldE, Transport* newE)
{
	transport->mod(oldE, newE);
	transport->saveToFile();
}

template <class T> int Service::size() { return 0; }

template <> int Service::size<User>()
{
	return user->size();
}

template <> int Service::size<Transport>()
{
	return transport->size();
}

template <class T> vector<T*>& Service::all() { return NULL; }

template <> vector<User*>& Service::all<User>()
{
	return user->all();
}

template <> vector<Transport*>& Service::all<Transport>()
{
	return transport->all();
}

template <class T> T* Service::at(int pos) { return NULL; }

template <> User* Service::at<User>(int pos) { return user->at(pos); }

template <> Transport* Service::at<Transport>(int pos) { return transport->at(pos); }

bool Service::login(const char* name, const char* pass)
{
	for (auto it = user->all().begin(); it != user->all().end(); ++it)
		if (strcmp((*it)->getName(), name) == 0 && strcmp((*it)->getPassword(), pass) == 0)
			return 1;
	return 0;
}

void Service::csv_or_txt(const char* type)
{
	if (strcmp(type, "csv") == 0)
	{
		transport = new RepoFileCSV<Transport>("TRANSPORT.CSV");
		user = new RepoFileCSV<User>("USER.CSV");
		transport->loadFromFile();
		user->loadFromFile();
		return;
	}
	if (strcmp(type, "txt") == 0)
	{
		if (transport)
			delete transport;
		if (user)
			delete user;
		transport = new RepoFileTXT<Transport>("TRANSPORT.TXT");
		user = new RepoFileTXT<User>("USER.TXT");
		transport->loadFromFile();
		user->loadFromFile();
		return;
	}
	throw CodeNameException("Tip de fisier indisponibil!");
}

User* Service::find_by_name(const char* name)
{
	for (auto it = user->all().begin(); it != user->all().end(); ++it)
		if (strcmp((*it)->getName(), name) == 0)
			return *it;
	return NULL;
}

Transport* Service::find_by_code(const char* code)
{
	for (auto it = transport->all().begin(); it != transport->all().end(); ++it)
		if (strcmp((*it)->getCode(), code) == 0)
			return *it;
	return NULL;
}

void Service::delete_t(Transport* t)
{
	del<Transport>(t);
	int i = 0;
	while (transport->at(i) != NULL)
	{
		Transport* crt = transport->at(i);
		if (t->getDate() == crt->getDate())
		{
			if (strcmp(t->getDeparture(), crt->getArrival()) == 0 || strcmp(crt->getDeparture(), t->getArrival()) == 0)
			{
				del<Transport>(crt);
				i--;
			}
		}
		i++;
	}
}

void Service::empty()
{
	for (auto it = transport->all().begin(); it != transport->all().end(); ++it)
		delete (*it);
	transport->all().clear();
	transport->saveToFile();
}

			//Transport* Service::find_by_code_and_arrival(const char* code, const char* arrival)
			//{
			//	for (auto it = transport->all().begin(); it != transport->all().end(); ++it)
			//	{
			//		if (strcmp((*it)->getCode(), code) == 0 && strcmp((*it)->getArrival(), arrival) == 0)
			//			return *it;
			//		if (strcmp((*it)->getCode(), code) == 0)
			//			throw DeleteException1();
			//	}
			//	throw DeleteException2();
			//}