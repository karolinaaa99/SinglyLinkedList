#include <iostream>

using namespace std;

class Elem 
{
private:
	int v; //key, data
	Elem* next_elem; //next

public:
	Elem();				//tworzy pusty element, konstruktor
	Elem(int x);			//tworzy element przechowujący x, drugi konstruktor
	int value();			//zwraca wartość v
	void setValue(int v);		//ustawia warość v
	Elem* next();			//zwraca następny element
	void setNext(Elem* p);		//ustawia p jako następny element
};

Elem::Elem()
{
	next_elem = NULL;
	v = 0; //zeby byla jakas wartosc
}

Elem::Elem(int x)
{
	next_elem = NULL;
	v = x;
}

int Elem::value()
{
	return v;
}

void Elem::setValue(int v)
{
	this->v = v; //stary v staje sie nowym v, ten obiekt, do którego sie konkretnie odwołuje
}

Elem* Elem::next()
{
	return next_elem;
}

void Elem::setNext(Elem* p)
{
	next_elem = p;
}

class SortedSLList 
{
private:
	Elem* head;			//wskaźnik na pierwszy element list
	Elem* tail;			//wskaźnik na ostatni element list
	int list_size;			//długość listy

public:
	SortedSLList();				//tworzy pustą listę, konstruktor
	bool empty();				//zwraca prawdę jeśli lista pusta, fałsz w przeciwnym przypadku
	int size();				//zwraca wielkość listy (liczbę elementów w liście)
	Elem* first();  			//zwraca pozycję pierwszego elementu
	Elem* last();   			//zwraca pozycję ostatniego elementu
	Elem* next(Elem* p);			//zwraca pozycję elementu następnego za p
	Elem* prev(Elem* p);			//zwraca pozycję elementu poprzedzającego p
	int retrieve(Elem* p); 			//zwraca element z pozycji p
	Elem* locate(int x);  			//zwraca pozycję pierwszego wystąpienia elementu x, NULL jeśli x nie występuje, wyszukiwanie liniowe
	void insert(int x); 			//wstawia x z zachowniem porządku
	void del(int x);      			//usuwa pierwsze wystąpienie element x
	void delAllx(int x);     //usuwa wszytkie wystapienia elementu x
	void clear();				//usuwa całą listę
	friend ostream& operator<<(ostream& out, SortedSLList& l); //wypisuje elementu listy
};

SortedSLList::SortedSLList()
{
	head = NULL;
	tail = NULL;
	list_size = 0;
}

bool SortedSLList::empty()
{
	/**if (list_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}**/

	if (list_size == 0)
		return true;
	return false;
}

int SortedSLList::size()
{
	return list_size;
}

Elem* SortedSLList::first()
{
	return head;
}

Elem* SortedSLList::last()
{
	return tail;
}

Elem* SortedSLList::next(Elem* p)
{
	/**if (empty() || head == tail) //lista jest pusta lub jednoelementowa
	{
		return NULL;
	}
	else if (p == tail) //p jest ogonem
	{
		return NULL;
	}**/

	if (empty())
		return NULL;
	else if (head == tail)
		return NULL;
	else if (p == tail)
		return NULL;
	return p->next(); //strzałka bo p jest wskaznikiem
}

Elem* SortedSLList::prev(Elem* p)
{
	/**if (empty() || head==tail)
	{
		return NULL;
	}
	if (p == head) 
	{
		return NULL;
	}**/

	if (empty())
		return NULL;
	else if (head == tail)
		return NULL;
	else if (p == head)
		return NULL;
	Elem* temp = head;
	while (temp->next() != p) 
	{
		temp = temp->next();
	}
	return temp;
}

int SortedSLList::retrieve(Elem* p)
{
	/**if (empty()) return NULL;
	else return p->value();**/

	if (empty())
		return NULL;
	return p->value();
}

Elem* SortedSLList::locate(int x)
{
	if (empty())
	{
		return NULL;
	}
	Elem* p = head;
	while (p->value() != x) 
	{
		if (p == tail)
			return NULL;
		p = p->next();
	}

	return p;
}

void SortedSLList::insert(int x)
{
	if (empty())
	{
		head = new Elem(x); //wywolujemy drugi konstruktor, tworze pierwszy element listy
		tail = head;
		list_size++;

		//drugi sposob, mysle, ze jest tez ok
		//Elem* p = new Elem(x);
		//head = tail = p;
		//list_size++;
	}
	else
	{
		if (head->value() >= x) //tworze nowy element przed dochczasowa head
		{
			Elem* p = new Elem;
			p->setValue(x);
			p->setNext(head);
			head = p;
			list_size++;
		}
		else
		{
			if (head == tail) //jesli lista jest jednoelementowa i nowy element jest wiekszy od head to tworze nowy tail
			{
				tail = new Elem(x);
				tail->setValue(x);
				head->setNext(tail);
				list_size++;
			}
			Elem* p = head;
			while (p->next()->value() < x)
			{
				p = p->next();
				if (tail == p) //nowy element jest wiekszy od dotychczasowego tail, czyli tworze nowy tail
				{
					tail = new Elem(x);
					tail->setValue(x);
					p->setNext(tail);
					list_size++;
					break;
				}
			}
			Elem* newElem = new Elem(x); //tworze nowy element wewnatrz listy
			newElem->setNext(p->next());
			p->setNext(newElem);
			list_size++;
		}
	}

	//kod ponizej dziala zle, w jednym miejscu jest blad
	/**if (empty()) //jesli lista jest pusta
	{
		Elem* p = new Elem(x);
		head = tail = p;
		list_size++;
	}
	else //jesli lista nie jest pusta
	{
		if (head == tail)  //lista jest jednoelementowa
		{
			if (x <= head->value()) //new head
			{
				Elem* p = new Elem(x);
				p->setNext(head);
				tail=head;
				head = p;
				list_size++;
			}
			else //new tail
			{
				Elem* p = new Elem(x);
				tail->setNext(p);
				head=tail;
				tail = p;
				list_size++;
			}
		}
		else //lista nie jest jednoelementowa, czyli jest co najmniej dwuelementowa
		{
			if (x <= head->value()) //new head
			{
				Elem* p = new Elem(x);
				p->setNext(head);
				head = p;
				list_size++;
			}
			else if (x >= tail->value())
			{
				Elem* p = new Elem(x);
				tail->setNext(p);
				tail = p;
				list_size++;
			}
			else //wstawiam elemnt pomiedzy head i tail
			{
				Elem* p = new Elem(x);
				Elem* temp = head;
				while (temp != tail)
				{
					if ((p->value() >= temp->value()) && (p->value() <= temp->next()->value()))
					{
						p->setNext(temp->next());
						temp->setNext(p);
						list_size++;
						break;
					}
					temp = temp->next();
				}
			}
		}
	}**/
}

void SortedSLList::del(int x)
{
	Elem* p = locate(x);
	if (p == NULL)
		return;
	else if (p == head)
	{
		head = head->next();
		delete p;
		list_size--;
	}
	else if (p != tail) 
	{
		Elem* prev = this->prev(p);
		prev->setNext(p->next());
		delete p;
		list_size--;
	}
	else
	{
		Elem* prev = this->prev(p);
		tail = prev;
		tail->setNext(NULL);
		delete p;
		list_size--;
	}
}

void SortedSLList::clear()
{
	if (empty())
	{
		return;
	}
	else
	{
		while (head != NULL)
		{
			Elem* p = head;
			head = head->next();
			delete p;
		}
	}
}

void SortedSLList::delAllx(int x)
{
	if (empty())
		return;
	else 
	{
		Elem* p = locate(x);
		while(p != NULL)
		{
			p = locate(x);
			if (p == NULL)
				break;
			Elem* previous = prev(p);
			if (previous != NULL)
			{
				previous->setNext(p->next());
				delete p;
			}
			else
			{
				head = head->next();
				delete p;
			}
		}

		/*
		Elem* p;
		while (true)
		{
			p = locate(x);
			if(p == NULL)
				break;
			Elem* previous = prev(p);
			if (previous != NULL)
			{
				previous->setNext(p->next());
				delete p;
			}
			else
			{
				head = head->next();
				delete p;
			}
		}*/
	}
}

ostream& operator<<(ostream& out, SortedSLList& l) 
{
	if (l.head == NULL)
		return out;
	Elem* temp = l.head;
	do {
		out << temp->value() << " ";
		temp = temp->next();
	} while (temp != l.tail);
	return out;
}

int main()
{
	SortedSLList lista;
	lista.insert(5);
	lista.insert(5);
	lista.insert(5);
	lista.insert(2);
	lista.insert(2);
	lista.insert(6);
	lista.insert(1);
	lista.insert(6);
	cout << lista;
	cout << endl;

	lista.delAllx(2);
	cout << lista;
	return 0;
}