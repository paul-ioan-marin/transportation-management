#include "Utilities.h"

vector<string> readLine(string line, const char del)
{
	stringstream ss(line);
	string item;
	vector<string> elements;
	while (getline(ss, item, del))
		elements.push_back(item);
	return elements;
}

void split(string& line, string& name, const char del)
{
	stringstream ss(line);
	getline(ss, name, del);
	string aux;
	getline(ss, aux);
	line = aux;
}

Date date_str(string line)
{
	stringstream ss(line);
	string item;
	vector<int> elements;
	while (getline(ss, item, '/'))
	{
		try
		{
			elements.push_back(stoi(item));
		}
		catch (exception& exc)
		{
			throw runtime_error("Ati introdus data gresit!");
		}
	}
	if (elements.size() != 3)
		throw runtime_error("Ati introdus data gresit!");
	return Date(elements[0], elements[1], elements[2]);
}

void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd     color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}