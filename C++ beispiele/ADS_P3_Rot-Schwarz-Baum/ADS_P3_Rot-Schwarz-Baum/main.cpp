/*************************************************
* ADS Praktikum 2.2
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "Tree.h"
#include "catch.h"

using namespace std;

///////////////////////////////////////
// Hilfsmethoden fürs Menü hier:
void buildMenu();
void buildInsertMenu(Tree&);
void buildSearchMenu(Tree&);
void buildImportMenu(Tree&);
void buildDeleteMenu(Tree&);
//
///////////////////////////////////////
int main() {

	int result = Catch::Session().run();

	///////////////////////////////////////
	// Ihr Code hier:
	Tree t;

	int benutzereingabe;
	bool exitCode = false;
	/*buildMenu();*/

	while (exitCode != true)
	{
		buildMenu();
		cout << "?> ";
		cin >> benutzereingabe;
		switch (benutzereingabe)
		{
		case 1:
			buildInsertMenu(t);
			break;
		case 2:
			buildImportMenu(t);
			break;
		case 3:
			buildDeleteMenu(t);
			break;
		case 4:
			buildSearchMenu(t);
			break;
		case 5:
			system("cls");
			t.printAll();
			break;
		case 6:
			system("cls");
			t.printLevelOrder();
			break;
		default:
			cout << "Wrong input." << endl;
			cout << "Good Bye" << endl;
			exitCode = true;
			break;


		}
		//system("PAUSE");
		//system("cls");

	}


	//
	///////////////////////////////////////
	system("PAUSE");

	return 0;
}

void buildMenu()
{
	cout << endl;
	cout << "=================================" << endl;
	cout << "1) Datensatz einfuegen, manuell" << endl;
	cout << "2) Datensatz einfuegen, CSV Datei" << endl;
	cout << "3) Datensatz loeschen" << endl;
	cout << "4) Suchen" << endl;
	cout << "5) Ausgabe in Preorder" << endl;
	cout << "6) Ausgabe in Levelorder" << endl;
}

void buildInsertMenu(Tree& tree)
{

	cout << "+ Bitte geben Sie den Datensatz ein" << endl;

	cout << "Name ?> ";
	string name;
	cin.clear();
	cin.ignore();
	getline(cin, name);

	cout << "Alter ?> ";
	int alter;
	cin.clear();
	//cin.ignore();
	cin >> alter;

	cout << "Einkommen ?> ";
	double einkommen;
	cin.clear();
	cin.ignore();
	cin >> einkommen;

	cout << "PLZ ?> ";
	int plz;
	cin.clear();
	cin.ignore();
	cin >> plz;

	tree.addNode(name, alter, einkommen, plz);

	system("cls");

	cout << "+ Ihr Datensatz wurde eingefuegt" << endl;



}

void buildSearchMenu(Tree& tree)
{
	string Name;
	cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
	cout << "Name ?> ";
	cin.clear();
	cin.ignore();
	getline(cin, Name);

	system("cls");

	cout << "+ Fundstellen:" << endl;

	if (!tree.searchNode(Name))
		cout << "keine" << endl;

}

void buildImportMenu(Tree& tree)
{
	string eineZeile = "";
	string auswahl;
	cout << "+ Moechten Sie die Daten aus der Datei \"ExportZielanalyse.csv\" importieren (j/n) ?> ";
	cin.clear();
	cin.ignore();
	getline(cin, auswahl);
	system("cls");

	if (auswahl[0] == 'j')
	{

		fstream read("ExportZielanalyse.csv", ios::in);

		while (getline(read, eineZeile))
		{
			//cout << eineZeile << endl;

			int actValue = 0;
			string currentPart = "";

			string name = "";
			int alter = 0;
			double einkommen = 0.0;
			int plz = 0;


			for (int i = 0; i < eineZeile.length(); i++)
			{
				if (eineZeile[i] != ';')
				{
					currentPart += eineZeile[i];
				}
				else
				{
					switch (actValue)
					{
					case 0:
						name = currentPart;
						break;
					case 1:
						alter = atoi(currentPart.c_str());
						break;
					case 2:
						einkommen = atoi(currentPart.c_str());

						plz = atoi(currentPart.c_str());
					default:
						break;
					}

					currentPart = "";

					actValue++;
				}

				if (i == eineZeile.length() - 1)
					plz = atoi(currentPart.c_str());

			}

			tree.addNode(name, alter, einkommen, plz);

		}

		if (read.eof())
			cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;

	}
	else
	{
		cout << "+ Importieren abgebrochen." << endl;
	}
}

void buildDeleteMenu(Tree& tree)
{
	int toDelete = 0;

	string zuLoeschendeZahl;
	cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << endl;
	cout << "PosID ?> ";
	cin.clear();
	cin.ignore();
	getline(cin, zuLoeschendeZahl);


	tree.deleteNode(atoi(zuLoeschendeZahl.c_str()));

}

