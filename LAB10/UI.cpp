#include "UI.h"

UI::UI() {}

UI::~UI() {}

template <class T> void UI::all() {}
template <> void UI::all<User>()
{
	if (service.all<User>().size() == 0)
		cout << "Niciun utilizator momentan!";
	else
	{
		cout << "Utilizatori:";
		for (auto it = service.all<User>().begin(); it != service.all<User>().end(); ++it)
			cout << endl << (*it)->toString();
	}
}
template <> void UI::all<Transport>()
{
	if (service.all<Transport>().size() == 0)
		cout << "Nicio calatorie momentan";
	else
	{
		cout << "Calatorii:";
		for (auto it = service.all<Transport>().begin(); it != service.all<Transport>().end(); ++it)
		{
			if ((*it)->getTotal_seat() == (*it)->getBooked_seat())
				SetColor(3);
			cout << endl << (*it)->toString();
			SetColor(0);
		}
	}
}

void UI::user()
{
	try
	{
		string opt;
		cout << "Introduceti: <add> pentru adaugare; <del> pentru stergere; <mod> pentru modificare; <all> pentru afisare totala; <x> pentru intoarcere" << endl;
		cout << "Introduceti: ";
		cin >> opt;
		if (opt == "add")
		{
			char* name = new char[30];
			char* password = new char[30];
			cout << "Introduceti numele: ";
			cin >> name;
			if (service.find_by_name(name) != NULL)
			{
				delete[] name;
				delete[] password;
				throw CodeNameException("Nume utilizat deja!");
			}
			cout << "Introduceti parola: ";
			cin >> password;
			service.add<User>(new User(name, password));
			cout << "Adaugat!";
			delete[] name;
			delete[] password;
		}
		else if (opt == "del")
		{
			char* name = new char[30];
			cout << "Introduceti numele: ";
			cin >> name;
			if (service.find_by_name(name) == NULL)
			{
				delete[] name;
				throw CodeNameException("Nume inexistent!");
			}
			service.del<User>(service.find_by_name(name));
			cout << "Sters!";
			delete[] name;
		}
		else if (opt == "mod")
		{
			char* oldName = new char[30];
			cout << "Introduceti vechiul nume: ";
			cin >> oldName;
			if (service.find_by_name(oldName) == NULL)
			{
				delete[] oldName;
				throw CodeNameException("Nume inexistent!");
			}
			char* name = new char[30];
			char* password = new char[30];
			cout << "Introduceti numele: ";
			cin >> name;
			if (service.find_by_name(name) != NULL && strcmp(oldName, name) != 0)
			{
				delete[] oldName;
				delete[] name;
				delete[] password;
				throw CodeNameException("Nume utilizat deja!");
			}
			cout << "Introduceti parola: ";
			cin >> password;
			service.mod<User>(service.find_by_name(oldName), new User(name, password));
			cout << "Modificat!";
			delete[] oldName;
			delete[] name;
			delete[] password;
		}
		else if (opt == "all")
		{
			all<User>();
		}
		else if (opt == "x")
			return;
		else throw InputException("Comanda invalida!");
	}
	catch (exception& exc)
	{
		cout << exc.what();
	}
	cout << endl;
	user();
}

void UI::transport()
{
	try
	{
		string opt;
		cout << "Introduceti: <add> pentru adaugare; <del> pentru stergere; <mod> pentru modificare; <all> pentru afisare totala; <x> pentru intoarcere" << endl;
		cout << "Introduceti: ";
		cin >> opt;
		if (opt == "add")
		{
			string opt_2;
			cout << "Doriti <autobuz> sau <avion>?" << endl << "Introduceti: ";
			cin >> opt_2;
			if (opt_2 == "autobuz")
			{
				char* code = new char[30];
				char* departure = new char[30];
				char* arrival = new char[30];
				Date date;
				string time, total_seats, booked_seats;
				cout << "Introduceti codul: ";
				cin >> code;
				if (service.find_by_code(code) != NULL)
				{
					delete[] code;
					delete[] departure;
					delete[] arrival;
					throw CodeNameException("Cod utilizat deja!");
				}
				cout << "Introduceti locatia plecarii: ";
				cin >> departure;
				cout << "Introduceti locatia destiantiei: ";
				cin >> arrival;
				cout << "Introduceti data plecarii sub forma <dd/mm/yyyy>: ";
				cin >> date;
				cout << "Introduceti durata calatoriei: ";
				try
				{
					cin >> time;
					if (stoi(time) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] code;
					delete[] departure;
					delete[] arrival;
					throw InputException("Durata calatoriei trebuie sa fie un numar natural strict pozitiv!");
				}
				cout << "Introduceti numarul de locuri totale: ";
				try
				{
					cin >> total_seats;
					if (stoi(total_seats) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] code;
					delete[] departure;
					delete[] arrival;
					throw InputException("Numarul de locuri trebuie sa fie un numar natural strict pozitiv!");
				}
				cout << "Introduceti numarul de locuri rezervate: ";
				try
				{
					cin >> booked_seats;
					if (stoi(booked_seats) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] code;
					delete[] departure;
					delete[] arrival;
					throw InputException("Numarul de locuri trebuie sa fie un numar natural strict pozitiv!");
				}				
				service.add<Transport>(new Bus(code, departure, arrival, date, stoi(time), stoi(total_seats), stoi(booked_seats)));
				cout << "Adaugat!";
				delete[] code;
				delete[] departure;
				delete[] arrival;
			}
			else if (opt_2 == "avion")
			{
				char* code = new char[30];
				char* departure = new char[30];
				char* arrival = new char[30];
				Date date;
				char* transit = new char[30];
				string total_seats, booked_seats;
				cout << "Introduceti codul: ";
				cin >> code;
				if (service.find_by_code(code) != NULL)
				{
					delete[] code;
					delete[] departure;
					delete[] arrival;
					delete[] transit;
					throw CodeNameException("Cod utilizat deja!");
				}
				cout << "Introduceti locatia plecarii: ";
				cin >> departure;
				cout << "Introduceti locatia destiantiei: ";
				cin >> arrival;
				cout << "Introduceti data plecarii sub forma <dd/mm/yyyy>: ";
				cin >> date;
				cout << "Este cu escala calatoria? Introduceti <da> sau <nu>: ";
				cin >> transit;
				cout << "Introduceti numarul de locuri totale: ";
				try
				{
					cin >> total_seats;
					if (stoi(total_seats) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] code;
					delete[] departure;
					delete[] arrival;
					delete[] transit;
					throw InputException("Numarul de locuri trebuie sa fie un numar natural strict pozitiv!");
				}
				cout << "Introduceti numarul de locuri rezervate: ";
				try
				{
					cin >> booked_seats;
					if (stoi(booked_seats) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] code;
					delete[] departure;
					delete[] arrival;
					delete[] transit;
					throw InputException("Numarul de locuri trebuie sa fie un numar natural strict pozitiv!");
				}
				service.add<Transport>(new Plane(code, departure, arrival, date, transit, stoi(total_seats), stoi(booked_seats)));
				cout << "Adaugat!";
				delete[] code;
				delete[] departure;
				delete[] arrival;
				delete[] transit;
			}
			else throw InputException("Comanda invalida!");
		}
		else if (opt == "del")
		{
			char* code = new char[30];
			cout << "Introduceti codul: ";
			cin >> code;
			if (service.find_by_code(code) == NULL)
			{
				delete[] code;
				throw CodeNameException("Cod inexistent!");
			}
			service.del<Transport>(service.find_by_code(code));
			cout << "Sters!";
			delete[] code;
		}
		else if (opt == "mod")
		{
			char* oldCode = new char[30];
			cout << "Introduceti codul: ";
			cin >> oldCode;
			if (service.find_by_code(oldCode) == NULL)
			{
				delete[] oldCode;
				throw CodeNameException("Cod inexistent!");
			}
			string opt_2;
			cout << "Doriti <autobuz> sau <avion>?" << endl << "Introduceti: ";
			cin >> opt_2;
			if (opt_2 == "autobuz")
			{
				char* code = new char[30];
				char* departure = new char[30];
				char* arrival = new char[30];
				Date date;
				string time, total_seats, booked_seats;
				cout << "Introduceti codul: ";
				cin >> code;
				if (service.find_by_code(code) != NULL && strcmp(oldCode, code) != 0)
				{
					delete[] oldCode;
					delete[] code;
					delete[] departure;
					delete[] arrival;
					throw CodeNameException("Cod utilizat deja!");
				}
				cout << "Introduceti locatia plecarii: ";
				cin >> departure;
				cout << "Introduceti locatia destinatiei: ";
				cin >> arrival;
				cout << "Introduceti data plecarii sub forma <dd/mm/yyyy>: ";
				cin >> date;
				cout << "Introduceti durata calatoriei: ";
				try
				{
					cin >> time;
					if (stoi(time) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] oldCode;
					delete[] code;
					delete[] departure;
					delete[] arrival;
					throw InputException("Durata calatoriei trebuie sa fie un numar natural strict pozitiv!");
				}
				cout << "Introduceti numarul de locuri totale: ";
				try
				{
					cin >> total_seats;
					if (stoi(total_seats) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] oldCode;
					delete[] code;
					delete[] departure;
					delete[] arrival;
					throw InputException("Numarul de locuri trebuie sa fie un numar natural strict pozitiv!");
				}
				cout << "Introduceti numarul de locuri rezervate: ";
				try
				{
					cin >> booked_seats;
					if (stoi(booked_seats) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] oldCode;
					delete[] code;
					delete[] departure;
					delete[] arrival;
					throw InputException("Numarul de locuri trebuie sa fie un numar natural strict pozitiv!");
				}
				service.mod<Transport>(service.find_by_code(oldCode), new Bus(code, departure, arrival, date, stoi(time), stoi(total_seats), stoi(booked_seats)));
				cout << "Modificat!";
				delete[] oldCode;
				delete[] code;
				delete[] departure;
				delete[] arrival;
			}
			else if (opt_2 == "avion")
			{
				char* code = new char[30];
				char* departure = new char[30];
				char* arrival = new char[30];
				Date date;
				char* transit = new char[30];
				string total_seats, booked_seats;
				cout << "Introduceti codul: ";
				cin >> code;
				if (service.find_by_code(code) != NULL && strcmp(oldCode, code) != 0)
				{
					delete[] oldCode;
					delete[] code;
					delete[] departure;
					delete[] arrival;
					delete[] transit;
					throw CodeNameException("Cod utilizat deja!");
				}
				cout << "Introduceti locatia plecarii: ";
				cin >> departure;
				cout << "Introduceti locatia destinatiei: ";
				cin >> arrival;
				cout << "Introduceti data plecarii sub forma <dd/mm/yyyy>: ";
				cin >> date;
				cout << "Este cu escala calatoria? Introduceti <da> sau <nu>: ";
				cin >> transit;
				cout << "Introduceti numarul de locuri totale: ";
				try
				{
					cin >> total_seats;
					if (stoi(total_seats) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] code;
					delete[] departure;
					delete[] arrival;
					delete[] transit;
					throw InputException("Numarul de locuri trebuie sa fie un numar natural strict pozitiv!");
				}
				cout << "Introduceti numarul de locuri rezervate: ";
				try
				{
					cin >> booked_seats;
					if (stoi(booked_seats) <= 0)
						throw runtime_error(NULL);
				}
				catch (exception& exc)
				{
					delete[] code;
					delete[] departure;
					delete[] arrival;
					delete[] transit;
					throw InputException("Numarul de locuri trebuie sa fie un numar natural strict pozitiv!");
				}
				service.mod<Transport>(service.find_by_code(oldCode), new Plane(code, departure, arrival, date, transit, stoi(total_seats), stoi(booked_seats)));
				cout << "Modificat!";
				delete[] oldCode;
				delete[] code;
				delete[] departure;
				delete[] arrival;
				delete[] transit;
			}
			else throw InputException("Comanda invalida!");
		}
		else if (opt == "all")
		{
		all<Transport>();
		}
		else if (opt == "x")
			return;
		else throw InputException("Comanda invalida!");
	}
	catch (exception& exc)
	{
		cout << exc.what();
	}
	cout << endl;
	transport();
}

void UI::boss()
{
	try
	{
		string opt;
		cout << "Introduceti: <utilizator> pentru modificare utilizatori, <calatorie> pentru modificare calatorie, <x> pentru iesire" << endl;
		cout << "Introduceti: ";
		cin >> opt;
		if (opt == "utilizator")
			user();
		else if (opt == "calatorie")
			transport();
		else if (opt == "x")
			return;
		else throw InputException("Comanda invalida!");
	}
	catch (exception& exc)
	{
		cout << exc.what();
	}
	cout << endl;
	boss();

}

void UI::client()
{
	Customer c;
	try
	{
		string opt;
		cout << "Introduceti: <cautare> pentru cautare, <rezervare> pentru rezervare, <logout> pentru logout" << endl << "Introduceti: ";
		cin >> opt;
		if (opt == "cautare")
		{
			Date d;
			cout << "Introduceti data pentru cautare: ";
			cin >> d;
			vector<Transport*> result = c.search(service, d);
			if (result.size() == 0)
				cout << "Nu a fost gasita nicio calatorie cu aceasta data!";
			else
			{
				cout << "Rezultatele cautarii:";
				for (auto it = result.begin(); it != result.end(); ++it)
					cout << endl << (*it)->toString();
			}
		}
		else if (opt == "rezervare")
		{
			char* code = new char[30];
			string seats;
			cout << "Introduceti codul: ";
			cin >> code;
			if (service.find_by_code(code) == NULL)
			{
				delete[] code;
				throw CodeNameException("Cod inexistent!");
			}
			cout << "Introduceti numarul de locuri: ";
			try
			{
				cin >> seats;
				if (stoi(seats) <= 0)
					throw runtime_error(NULL);
			}
			catch (exception& exc)
			{
				delete[] code;
				throw InputException("Numarul de locuri trebuie sa fie un numar natural strict pozitiv!");
			}
			c.book(service, code, stoi(seats));
			cout << "Rezervare realizata!" << endl;
			all<Transport>();
		}
		else if (opt == "logout")
			return;
		else throw InputException("Comanda invalida!");
	}
	catch (exception& exc)
	{
		cout << exc.what();
	}
	cout << endl;
	client();
}

void UI::login(int tries)
{
	try
	{
		if (tries == 0)
		{
			cout << "Ati epuizat numarul de incercari!" << endl;
			return;
		}
		if (tries == 1)
			cout << "Mai aveti o singura incercare!" << endl;
		else
			cout << "Aveti " << tries << " incercari." << endl;
		char* name = new char[30];
		char* password = new char[30];
		cout << "Introduceti numele: ";
		cin >> name;
		cout << "Introduceti parola: ";
		cin >> password;
		if (service.login(name, password))
		{
			char* name_2 = new char[strlen(name) + 1];
			strcpy_s(name_2, strlen(name) + 1, name);
			name_2[0] = toupper(name_2[0]);
			cout << "Buna ziua, " << name_2 << "!" << endl;
			delete[] name_2;
			all<Transport>();
			cout << endl;
			client();
			delete[] name;
			delete[] password;
			login(3);
		}
		else
		{
			cout << "Nume sau parola incorecta!";
			delete[] name;
			delete[] password;
		}
		cout << endl;
	}
	catch (exception& exc)
	{
		cout << exc.what();
	}
	login(tries - 1);
}

void UI::show()
{
	try
	{
		char* opt_2 = new char[3];
		cout << "Doriti <csv> sau <txt>?" << endl << "Introduceti: ";
		cin >> opt_2;
		service.csv_or_txt(opt_2);
		string opt;
		cout << "Doriti <patron> sau <client>?" << endl << "Introduceti: ";
		cin >> opt;
		if (opt == "patron")
		{
			boss();
			cout << "La revedere!";
			return;
		}
		if (opt == "client")
		{
			cout << "Log-in:" << endl;
			login(3);
			cout << "La revedere!";
			return;
		}
		throw InputException("Comanda invalida!");
	}
	catch (exception& exc)
	{
		string opt_3;
		cout << exc.what() << endl;
		cout << "Reincercati? <da> sau <nu>? Introduceti: ";
		cin >> opt_3;
		if (opt_3 == "da")
			show();
		else if (opt_3 == "nu")
			cout << "La revedere!";
		else cout << "Nu stii sa scrii! Avem dreptul sa ne alegem clientii! Pa!";
	}
}