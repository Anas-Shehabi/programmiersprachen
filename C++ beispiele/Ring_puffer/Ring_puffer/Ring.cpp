#include <iostream>
#include "Ring.h"
#include"RingNode.h"
using namespace std;

Ring::Ring()
{
	AnzahlNodes = 0;
	anker = nullptr;
}

void Ring::addNode(string Des, string data) {
	RingNode* x = new RingNode(0, Des, data);
	RingNode* tmp = anker;
	if (anker == nullptr)
	{
		anker = x;
		anker->setNext(x);
		AnzahlNodes++;
	}
	else if (AnzahlNodes == 1)
	{

		x->setNext(tmp);
		anker = x;
		tmp->setNext(x);
		AnzahlNodes++;
	}

	else
	{
		while (true)
		{
			if (tmp->getNext()->getNext() == anker)
			{
				x->setNext(anker->getNext());
				anker->setNext(x);
				anker = x;
				AnzahlNodes++;
				break;
			}
			else
			{
				tmp = tmp->getNext();
			}
		}
	}
	RingNode* tmp2 = anker->getNext();
	while (tmp2 != anker)
	{
		int thal = tmp2->getAge() ;
		tmp2->setAge(++thal);
		if (tmp2->getAge() == 6)
		{
			anker->setNext(tmp2->getNext());
			RingNode* tmp3 = anker->getNext();
			delete tmp2;
			AnzahlNodes--;
			while (tmp3 != anker)
			{
				int thal = tmp3->getAge();
				tmp3->setAge(++thal);
				tmp3 = tmp3->getNext();
			}
			
			break;
		}
		tmp2 = tmp2->getNext();
	}


}

bool Ring::search(string Data) 
{
	
	RingNode * tmp = anker->getNext();
	if (anker->getData() == Data)
	{
		cout << "+ Gefunden in Backup: " << "OldAge: " << tmp->getAge() << ", Descr: " << tmp->getDescription() << " ,Data: "
			<< tmp->getData() << endl;
		return true;
	}
	while (tmp != anker)
	{
		if (tmp->getData() == Data)
		{
			cout << "+ Gefunden in Backup: " << "OldAge: " << tmp->getAge() << ", Descr: " << tmp->getDescription() << " ,Data: " <<
				tmp->getData() << endl;
			return true;
		}
		else
			tmp = tmp->getNext();

	}
	cout << "+ Datensatz konnte nicht gefunden werden." << endl;
	return false;
	
}

void Ring::print()
{
	RingNode * tmp = anker;
	do
	{
		cout << "OldAge: " << tmp->getAge() << ", Descr: " << tmp->getDescription() << " ,Data: " << tmp->getData() << endl
			<< " --------------------------" << endl;
		tmp = tmp->getNext();

	} while (tmp != anker);
	
}