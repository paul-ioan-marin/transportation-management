#pragma once
#include "RepoFile.h"

template <class T> class RepoFileTXT {};

template <> class RepoFileTXT<Transport> : public RepoFile<Transport>
{
private:
	char delimit = ' ';
public:
	RepoFileTXT() {}
	RepoFileTXT(const char* newFile) :RepoFile<Transport>(newFile) {};
	void saveToFile()
	{
		ofstream f(RepoFile<Transport>::fileName);
		f.clear();
		for (Transport* crt : IRepo<Transport>::elem)
			f << crt->className() << delimit << crt->toStringFile(delimit) << endl;
		f.close();
	}
	void save(Transport* crt)
	{
		ofstream f(RepoFile<Transport>::fileName);
		f << crt->className() << delimit << crt->toStringFile(delimit) << endl;
		f.close();
	}
	void loadFromFile()
	{
		string line;
		string name;
		ifstream f(RepoFile<Transport>::fileName);
		Transport* ent;
		while (!f.eof())
		{
			getline(f, line);
			if (line == "")
				return;
			split(line, name, delimit);
			if (name == "Plane")
			{
				ent = new Plane(line, delimit);
				for (Transport* crt : IRepo<Transport>::elem)
					if (strcmp(crt->getCode(), ent->getCode()) == 0)
					{
						delete ent;
						throw CodeNameException("Cod utilizat deja!");
					}
				IRepo<Transport>::add(ent);
				delete[] ent;
			}
			if (name == "Bus")
			{
				ent = new Bus(line, delimit);
				for (Transport* crt : IRepo<Transport>::elem)
					if (strcmp(crt->getCode(), ent->getCode()) == 0)
					{
						delete ent;
						throw CodeNameException("Cod utilizat deja!");
					}
				IRepo<Transport>::add(ent);
				delete ent;
			}
		}
		f.close();
	}
	~RepoFileTXT() {}
};

template <> class RepoFileTXT<User> : public RepoFile<User>
{
private:
	char delimit = ' ';
public:
	RepoFileTXT() {}
	RepoFileTXT(const char* newFile) :RepoFile<User>(newFile) {}
	void saveToFile()
	{
		ofstream f(RepoFile<User>::fileName);
		f.clear();
		for (User* crt : IRepo<User>::elem)
			f << crt->toStringFile(delimit) << endl;
		f.close();
	}
	void save(User* crt)
	{
		ofstream f(RepoFile<User>::fileName);
		f << crt->toStringFile(delimit) << endl;
		f.close();
	}
	void loadFromFile()
	{
		ifstream f(RepoFile<User>::fileName);
		string line;
		User* ent;
		while (!f.eof())
		{
			getline(f, line);
			if (line == "")
				return;
			ent = new User(line, delimit);
			for (User* crt : IRepo<User>::elem)
				if (strcmp(crt->getName(), ent->getName()) == 0)
				{
					delete ent;
					throw CodeNameException("Nume utilizat deja!");
				}
			IRepo<User>::add(ent);
			delete ent;
		}
		f.close();
	}
	~RepoFileTXT() {}
};