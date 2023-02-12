#include "Test.h"

void resetElements(Service& service, vector<Transport*> defaultTrips)
{
	service.empty();
	for (Transport* t : defaultTrips)
		service.add(t);
}

void TesteCristina_3()
{
	Transport* t1 = new Plane("156", "ClujNapoca", "Dubai", "14/6/2020", "nu", 100, 80);
	Transport* t2 = new Bus("873", "Constanta", "ClujNapoca", "15/7/2020", 1, 40, 20);
	Transport* t3 = new Bus("118", "Viena", "Bucuresti", "14/6/2020", 3, 80, 50);
	Transport* t4 = new Plane("122", "Bucuresti", "ClujNapoca", "14/6/2020", "nu", 100, 80);
	Transport* t5 = new Plane("122", "ClujNapoca", "Bucuresti", "14/6/2020", "nu", 100, 80);
	Service service("txt", "Text1.txt", "Text2.txt");
	vector<Transport*> defaultTrips;
	defaultTrips.push_back(t1);
	defaultTrips.push_back(t2);
	defaultTrips.push_back(t3);
	defaultTrips.push_back(t4);
	defaultTrips.push_back(t5);
	resetElements(service, defaultTrips);
	service.delete_t(t1);
	assert(service.size<Transport>() == 3);
	assert(*service.at<Transport>(0) == *t2);
	assert(*service.at<Transport>(1) == *t3);
	assert(*service.at<Transport>(2) == *t5);
	resetElements(service, defaultTrips);
	service.delete_t(t2);
	assert(service.size<Transport>() == 4);
	assert(*service.at<Transport>(0) == *t1);
	assert(*service.at<Transport>(1) == *t3);
	assert(*service.at<Transport>(2) == *t4);
	assert(*service.at<Transport>(3) == *t5);
	resetElements(service, defaultTrips);
	service.delete_t(t3);
	assert(service.size<Transport>() == 3);
	assert(*service.at<Transport>(0) == *t1);
	assert(*service.at<Transport>(1) == *t2);
	assert(*service.at<Transport>(2) == *t5);
	resetElements(service, defaultTrips);
	service.delete_t(t4);
	assert(service.size<Transport>() == 1);
	assert(*service.at<Transport>(0) == *t2);
	resetElements(service, defaultTrips);
	service.delete_t(t5);
	assert(service.size<Transport>() == 3);
	assert(*service.at<Transport>(0) == *t1);
	assert(*service.at<Transport>(1) == *t2);
	assert(*service.at<Transport>(2) == *t3);
	cout << "Teste trecute!" << endl;
	//ce e mai jos e ca sa pot rula de mai multe ori testul fara sa crape :/
	service.empty();
}


void Validator_test()
{
	Validator validator;
	Transport* t1 = new Bus("a,b,c,1/1/1,1,1,1", ',');
	try
	{
		validator.validate<Transport>(t1);
	}
	catch (exception& exc)
	{
		assert(false);
	}
	delete t1;
}

void Customer_test()
{
	Customer c;
	Service s_txt("txt", "Text.txt", "Test_user.txt");
	vector<Transport*> result = c.search(s_txt, Date(1, 1, 1));
	assert(result.size() == 1);
	assert(result.at(0) == s_txt.at<Transport>(0));
	c.book(s_txt, "a", 1);
	Transport* t = result.at(0)->clone();
	t->setBooked_seat(2);
	assert(*(s_txt.at<Transport>(0)) == (*t));
	t->setBooked_seat(1);
	s_txt.mod<Transport>(s_txt.at<Transport>(0), t);
	delete t;
}

void Entitati_test()
{
	Bus b;
	Bus b1("a", "b", "c", Date(1, 1, 1), 1, 1, 1);
	Bus b2(b1);
	Bus b3("a,b,c,1/1/1,1,1,1", ',');
	b.setCode("a");
	b.setDeparture("b");
	b.setArrival("c");
	b.setDate(Date(1, 1, 1));
	b.setTime(1);
	b.setTotal_seat(1);
	b.setBooked_seat(1);
	assert(strcmp(b.getCode(), b3.getCode()) == 0);
	assert(strcmp(b.getDeparture(), b3.getDeparture()) == 0);
	assert(strcmp(b.getArrival(), b3.getArrival()) == 0);
	assert(b.getDate() == b3.getDate());
	assert(b.getTime() == b3.getTime());
	assert(b.getTotal_seat() == b3.getTotal_seat());
	assert(b.getBooked_seat() == b3.getBooked_seat());
	Transport* pb = b.clone();
	assert(strcmp(b.getCode(), pb->getCode()) == 0);
	assert(b.toString()== "Cod: a Locatie plecare: b Locatie sosire: c Data plecare: 1/1/1 Durata calatorie: 1 Total locuri: 1 Locuri rezervate: 1");
	assert(b.toStringFile(',') == "a,b,c,1/1/1,1,1,1");
	assert(b.className() == "Bus");
	delete pb;

	Plane p;
	Plane p1("a", "b", "c", Date(1, 1, 1), "da" , 1, 1);
	Plane p2(p1);
	Plane p3("a,b,c,1/1/1,da,1,1", ',');
	p.setCode("a");
	p.setDeparture("b");
	p.setArrival("c");
	p.setDate(Date(1, 1, 1));
	p.setTransit("da");
	p.setTotal_seat(1);
	p.setBooked_seat(1);
	assert(strcmp(p.getCode(), p3.getCode()) == 0);
	assert(strcmp(p.getDeparture(), p3.getDeparture()) == 0);
	assert(strcmp(p.getArrival(), p3.getArrival()) == 0);
	assert(p.getDate() == p3.getDate());
	assert(strcmp(p.getTransit(), p3.getTransit()) == 0);
	assert(p.getTotal_seat() == p3.getTotal_seat());
	assert(p.getBooked_seat() == p3.getBooked_seat());
	Transport* pp = p.clone();
	assert(strcmp(p.getCode(), pp->getCode()) == 0);
	assert(p.toString() == "Cod: a Locatie plecare: b Locatie sosire: c Data plecare: 1/1/1 Escala: da Total locuri: 1 Locuri rezervate: 1");
	assert(p.toStringFile(',') == "a,b,c,1/1/1,da,1,1");
	assert(p.className() == "Plane");
	delete pp;

	User u;
	User u1("a", "a");
	User u2(u1);
	User u3("a,a", ',');
	u.setName("a");
	u.setPassword("a");
	assert(strcmp(u.getName(), u1.getName()) == 0);
	assert(strcmp(u.getPassword(), u1.getPassword()) == 0);
	assert(u == u1);
	User* pu = u.clone();
	assert(u == *pu);
	assert(u.toString() == "Nume: a Parola: a");
	assert(u.toStringFile(',') == "a,a");
	assert(u.className() == "User");
	delete pu;
}

void Repo_test()
{
	RepoFileTXT<Transport> repo_1;
	RepoFileTXT<Transport> repo_txt("Text.txt");
	RepoFileCSV<Transport> repo_csv("Csv.csv");
	repo_csv.loadFromFile();
	repo_txt.loadFromFile();
	assert(repo_txt.size() == 1);
	Transport* t1 = ((*repo_txt.all().begin()))->clone();
	repo_txt.del(t1);
	assert(repo_txt.size() == 0);
	Transport* t2 = new Bus("a a a 1/1/1 1 2 1", ' ');
	repo_txt.add(t2);
	assert(repo_txt.size() == 1);
	repo_txt.mod(t2, t1);
	repo_txt.saveToFile();
	assert(**(repo_csv.all().begin()) == (**(repo_txt.all().begin())));
	assert(repo_csv.size() == 1);
	Transport* c1 = (*(repo_csv.all().begin()))->clone();
	repo_csv.del(c1);
	assert(repo_csv.size() == 0);
	Transport* c2 = new Bus("a a a 1/1/1 1 2 1", ' ');
	repo_csv.add(c2);
	assert(repo_csv.size() == 1);
	repo_csv.mod(c2, c1);
	repo_csv.saveToFile();
	assert(**(repo_csv.all().begin()) == (**(repo_txt.all().begin())));
	delete t1, t2, c1, c2;
}

void Service_test()
{
	Service s_txt("txt", "Text.txt", "Test_user.txt");
	assert(s_txt.size<Transport>() == 1);
	Transport* t1 = ((*s_txt.all<Transport>().begin()))->clone();
	s_txt.del<Transport>(t1);
	assert(s_txt.size<Transport>() == 0);
	Transport* t2 = new Bus("a a a 1/1/1 1 2 1", ' ');
	s_txt.add<Transport>(t1);
	s_txt.mod<Transport>(t1, t2);
	assert(**(s_txt.all<Transport>().begin()) == *t1);
	assert(s_txt.login("a", "a") == 1);
	assert(strcmp(s_txt.find_by_code("a")->getArrival(), "a") == 0);
	assert(strcmp(s_txt.find_by_name("a")->getPassword(), "a") == 0);
}

void Test()
{
	Entitati_test();
	Repo_test();
	Service_test();
	Validator_test();
	Customer_test();
}

			//void TesteCristina()
			//{
			//	IRepo<Transport>* repo = new RepoFileCSV<Transport>("fisier-111-2.csv");
			//	repo->loadFromFile();
			//	Transport* t1 = new Plane("1x54", "Cluj-Napoca", "Dubai", "14/06/2020", "nu", 100, 80);
			//	Transport* t2 = new Bus("39g0", "Constanta", "Brasov", "15/07/2020", 1, 40, 20);
			//	Transport* t3 = new Bus("41kl", "Bucuresti", "Vienna", "11/06/2020", 3, 80, 50);
			//	assert(repo->size() == 3);
			//	assert(*(repo->at(0)) == *t1);
			//	assert(*(repo->at(1)) == *t2);
			//	assert(*(repo->at(2)) == *t3);
			//	Transport* t4 = new Plane("h6pd", "Iasi", "Munchen", "20/09/2020", "da", 50, 10);
			//	repo->mod(t2, t4);
			//	assert(*(repo->at(0)) == *t1);
			//	assert(*(repo->at(1)) == *t3);
			//	assert(*(repo->at(2)) == *t4);
			//	repo->mod(t1, t2);
			//	assert(*(repo->at(0)) == *t3);
			//	assert(*(repo->at(1)) == *t4);
			//	assert(*(repo->at(2)) == *t2);
			//}
			
			//void TesteCristina_2()
			//{
			//	Service s("txt", "Text1.txt", "Text2.txt");
			//	Transport* t1 = new Plane("156", "Cluj-Napoca", "Dubai", "14/06/2020", "nu", 100, 80);
			//	Transport* t2 = new Bus("873", "Constanta", "Brasov", "15/07/2020", 1, 40, 20);
			//	Transport* t3 = new Bus("118", "Bucuresti", "Vienna", "11/06/2020", 3, 80, 50);
			//	s.add<Transport>(t1);
			//	s.add<Transport>(t2);
			//	s.add<Transport>(t3);
			//	try
			//	{
			//		s.del<Transport>(s.find_by_code_and_arrival("873", "Brasov"));
			//		assert(s.size<Transport>() == 2);
			//		assert(*(s.at<Transport>(0)) == *t1);
			//		assert(*(s.at<Transport>(1)) == *t3);
			//	}
			//	catch (DeleteException1& exc)
			//	{
			//		assert(false);
			//	}
			//	catch (DeleteException2& exc)
			//	{
			//		assert(false);
			//	}
			//	try
			//	{
			//		s.del<Transport>(s.find_by_code_and_arrival("156", "Paris"));
			//		assert(false);
			//	}
			//	catch (DeleteException1& exc)
			//	{
			//		cout << "DeleteException1 thrown" << endl;
			//		assert(s.size<Transport>() == 2);
			//		assert(*(s.at<Transport>(0)) == *t1);
			//		assert(*(s.at<Transport>(1)) == *t3);
			//
			//	}
			//	catch (DeleteException2& exc)
			//	{
			//		assert(false);
			//	}
			//	try
			//	{
			//		s.del<Transport>(s.find_by_code_and_arrival("667", "Fagaras"));
			//		assert(false);
			//	}
			//	catch (DeleteException1& exc)
			//	{
			//		assert(false);
			//
			//	}
			//	catch (DeleteException2& exc)
			//	{
			//		cout << "DeleteException2 thrown" << endl;
			//		assert(s.size<Transport>() == 2);
			//		assert(*(s.at<Transport>(0)) == *t1);
			//		assert(*(s.at<Transport>(1)) == *t3);
			//	}
			//	try
			//	{
			//		s.del<Transport>(s.find_by_code_and_arrival("156", "Paris"));
			//		assert(false);
			//	}
			//	catch (DeleteException2& exc)
			//	{
			//		cout << "DeleteException2 thrown" << endl;
			//	}
			//	catch (DeleteException1& exc)
			//	{
			//		assert(false);
			//	}
			//	try
			//	{
			//		s.del<Transport>(s.find_by_code_and_arrival("667", "Fagaras"));
			//		assert(false);
			//	}
			//	catch (DeleteException2& exc)
			//	{
			//		cout << "DeleteException2 thrown" << endl;
			//	}
			//	catch (DeleteException1& exc)
			//	{
			//		assert(false);
			//	}
			//	delete t1, t2, t3;
			//}