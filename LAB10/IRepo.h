#pragma once
#include "Validator.h"
#include "Plane.h"
#include "Bus.h"
#include "User.h"

template<class T> class IRepo
{
protected:
	vector<T*> elem;
	Validator validator;
public:
	IRepo() {}
	virtual ~IRepo() {}
	void add(T* ent)
	{
		for (auto it = elem.begin(); it != elem.end(); ++it)
			if (*ent == **it)
				throw ExistingException("Elementul exista deja!");
		validator.validate<T>(ent);
		elem.push_back(ent->clone());
	}
	void del(T* ent)
	{
		for (auto it = elem.begin(); it != elem.end(); ++it)
			if (*ent == **it)
			{
				delete *it;
				elem.erase(it);
				return;
			}
		throw ExistingException("Elementul nu exista!");
	}
	void mod(T* oldE, T* newE)
	{
		validator.validate<T>(newE);
		for (auto it = elem.begin(); it != elem.end(); ++it)
			if (*oldE == **it)
			{
				*it = newE->clone();
				return;
			}
		throw ExistingException("Elementul nu exista!");
	}
	int size() { return elem.size(); }
	vector<T*>& all() { return elem; }
	T* at(int i)
	{
		int j = 0;
		for (auto it = elem.begin(); it != elem.end(); ++it)
		{
			if (i == j)
				return *it;
			j++;
		}
		return NULL;
	}
	virtual void loadFromFile() = 0;
	virtual void saveToFile() = 0;
	virtual void save(T*) = 0;
};

