#pragma once
#include "IRepo.h"

template <class T> class RepoFile : public IRepo<T>
{
protected:
	char* fileName;
	char delimit;
public:
	RepoFile() { fileName = NULL; delimit = '\0'; };
	RepoFile(const char* newFile)
	{
		fileName = new char[strlen(newFile) + 1];
		strcpy_s(fileName, strlen(newFile) + 1, newFile);
		delimit = '\0';
	}
	~RepoFile() { if (fileName) delete[] fileName; }
};