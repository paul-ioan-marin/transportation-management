#include "Customer.h"

vector<Transport*> Customer::search(Service& serv, const Date& d)
{
	vector<Transport*> result;
	for (auto it = (serv.transport)->all().begin(); it != (serv.transport)->all().end(); ++it)
	{
		if ((*it)->getDate() == d)
			result.push_back(*it);
	}
	return result;
}
void Customer::book(Service& serv, const char* code, int seats)
{
	Transport* crt = serv.find_by_code(code);
	if (crt == NULL)
		throw CodeNameException("Cod inexistent!");
	int empty_seat = crt->getTotal_seat() - crt->getBooked_seat();
	if (seats > empty_seat)
	{
		if (empty_seat == 0)
			throw CommandException("Nu sunt este disponibil niciun loc!");
		if (empty_seat == 1)
			throw CommandException("Nu este disponibil decat un loc!");
		else
			throw CommandException("Nu sunt disponibile decat " + to_string(empty_seat) + " locuri!");
	}
	crt->setBooked_seat(crt->getBooked_seat() + seats);
	serv.transport->saveToFile();
}