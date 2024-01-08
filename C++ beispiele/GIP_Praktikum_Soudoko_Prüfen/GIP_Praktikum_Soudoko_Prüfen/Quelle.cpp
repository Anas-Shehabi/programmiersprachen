#include <iostream>
#include <string>

using namespace std;

int sudoku[9][9] = { 0 };

void sudoku_eingabe()
{
	string eingabe[11] = { };

	for (int m = 0; m < 11; m++)
	{
		getline(cin, eingabe[m]);
	}

	for (int i = 0, l = 0; i < 11; i++)
	{
		if (i % 4 != 3)
		{
			for (int j = 0, k = 0; j < eingabe[i].size(); j++)
			{
				if (eingabe[i].at(j) >= '0' && eingabe[i].at(j) <= '9')
				{
					sudoku[l][k] = eingabe[i].at(j) - '0';
					k++;
				}

			}
			l++;
		}
	}
}

void sudoku_ausgabe()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{

			std::cout << ";" << sudoku[i][j];
			if (j % 3 == 2 && j != 8)
			{
				std::cout << ";" << "//";
			}
		}
		std::cout << std::endl;
		if (i % 3 == 2 && i != 8)
		{
			std::cout << "=======//=======//=======" << std::endl;
		}
	}
}

void sudoku_pruefen()
{
	bool korrektes_sudoku = true;
	for (int i = 0; i < 9; i++) // Spalten überprüfen, durch durchgehen
	{
		unsigned int zahlen_anzahl[9] = { 0 };
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (sudoku[j][i] == k + 1)
				{
					zahlen_anzahl[k]++;
				}
			}
		}
		for (int k = 0; k < 9; k++)
		{
			if (zahlen_anzahl[k] == 0)
			{
				cout << "Spalte " << i << ": Zahl " << k + 1 << " kommt nicht vor." << endl;
				korrektes_sudoku = false;
			}
			else if (zahlen_anzahl[k] > 1)
			{
				cout << "Spalte " << i << ": Zahl " << k + 1 << " kommt mehrfach vor." << endl;
				korrektes_sudoku = false;
			}
		}
	}
	for (int i = 0; i < 9; i++) //Zeilen durchgehen Durch durchgehen
	{
		unsigned int zahlen_anzahl[9] = { 0 };
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (sudoku[i][j] == k + 1)
				{
					zahlen_anzahl[k]++;
				}
			}
		}
		for (int k = 0; k < 9; k++)
		{
			if (zahlen_anzahl[k] == 0)
			{
				cout << "Zeile " << i << ": Zahl " << k + 1 << " kommt nicht vor." << endl;
				korrektes_sudoku = false;
			}
			else if (zahlen_anzahl[k] > 1)
			{
				cout << "Zeile " << i << ": Zahl " << k + 1 << " kommt mehrfach vor." << endl;
				korrektes_sudoku = false;
			}
		}
	}
	for (int i = 0, spalte = 0, zeile = i % 3; i < 9; i++) //Block durchgehen
	{
		unsigned int zahlen_anzahl[9] = { 0 };
		zeile = i % 3; //Position des Blockes in der Aktuellen Zeile (erster, zweiter dritter)
		 // Position des Blockes in der Aktuellen Spalte (erste, zweite, drtte)
		for (int j = 0 + spalte * 3; j < 3 + spalte * 3; j++)
		{
			for (int k = 0 + zeile * 3; k < 3 + zeile * 3; k++)
			{
				for (int l = 0; l < 9; l++)
				{
					if (sudoku[j][k] == l + 1)
					{
						zahlen_anzahl[l]++;
					}
				}
			}
		}
		if (zeile == 2)
		{
			spalte++;
		}
		for (int k = 0; k < 9; k++)
		{
			if (zahlen_anzahl[k] == 0)
			{
				cout << "Block " << i << ": Zahl " << k + 1 << " kommt nicht vor." << endl;
				korrektes_sudoku = false;
			}
			else if (zahlen_anzahl[k] > 1)
			{
				cout << "Block " << i << ": Zahl " << k + 1 << " kommt mehrfach vor." << endl;
				korrektes_sudoku = false;
			}
		}
	}
	if (korrektes_sudoku == true)
	{
		cout << "Das Sudoku ist gueltig." << endl;
	}
}

int main()
{
	cout << "Bitte geben Sie das Sudoku ein:" << endl;
	sudoku_eingabe();
	//cout << endl << "Das Sudoku lautet:" << endl;
	//sudoku_ausgabe();
	sudoku_pruefen();
	system("PAUSE");
	return 0;
}