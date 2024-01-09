#include<iostream>
#include<string>
#include"Ring.h"
using namespace std;

int main() {

	Ring obj;
	obj.addNode("Fadi", "Aleppo");
	obj.addNode("Anas", "Damascus");
	obj.addNode("Maher", "Damascus");
	obj.addNode("Dirar", "Dara'a");
	obj.addNode("Alolo", "Hama");
	obj.addNode("Alhmidi", "Der Al-Zor");
	obj.addNode("Ibrahim", "Darra");

	/*obj.print();

	bool x = obj.search("Der Al-Zor");
	if (x == true)
		cout << "Es existiert"<<endl;
	else
	{
		cout << "es existiert nicht" << endl;

	}*/

	cout << "OneRingToRuleThemAll v0.1, by Sauron Schmidt" << endl
		<< "==================================" << endl		<< "1) Backup einfuegen" << endl		<< "2) Backup suchen" << endl		<< "3) Alle Backups ausgeben" << endl;	int wahl;		string Des = ""; string data = "";	bool result;	while (true)
	{
		cin >> wahl;
		switch (wahl)
		{
		case 1:

			cout << "+Neuen Datensatz einfuegen" << endl;
			cout << "Beschreibung ?> ";  cin >> Des;
			cout << "Daten ?> "; cin >> data;
			obj.addNode(Des, data);
			cout << " +Ihr Datensatz wurde hinzugefuegt." << endl;			break;		case 2:			cout << "+Nach welchen Daten soll gesucht werden? " << endl;			cin >> data;			result = obj.search(data);			break;		case 3:			obj.print();			break;
		default:
			break;
		}

	}	

	system("pause");
	return 0;

}