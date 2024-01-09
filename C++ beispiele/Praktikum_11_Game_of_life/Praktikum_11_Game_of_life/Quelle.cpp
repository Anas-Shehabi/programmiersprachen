#include <iostream>
#define CIMGGIP_MAIN
#include "CImgGIP05.h"
using namespace std;
using namespace cimg_library;

const int grid_size = 10; // Anzahl an Kaestchen in x- und y-Richtung
const int box_size = 30;  // size der einzelnen Kaestchen (in Pixel)
const int border = 20;    // Rand links und oben bis zu den ersten Kaestchen (in Pixel)

// Prototyp der Funktionen zum Vorbelegen des Grids ...
void grid_init(bool grid[][grid_size]);

int main()
{
	bool grid[grid_size][grid_size] = { 0 };
	bool next_grid[grid_size][grid_size] = { 0 };

	// Erstes Grid vorbelegen ...
	grid_init(grid);

	while (gip_window_not_closed())
	{
		// Spielfeld anzeigen ...
		// Ggfs gip_stop_updates();
		// TO DO
		gip_stop_updates();
		gip_draw_rectangle(border, border, border + grid_size * box_size, border + grid_size * box_size, white);
		for (int y = 0; y < grid_size; y++)
		{
			for (int x = 0; x < grid_size; x++)
			{

				if (grid[x][y] == true)
				{
					gip_draw_rectangle(border + x * box_size, border + y * box_size, border + (x + 1) * box_size, border + (y + 1) * box_size, green);
				}
			}
		}
		gip_start_updates();
		gip_sleep(3);

		// Berechne das naechste Spielfeld ...
		// Achtung; Für die Zelle (x,y) darf die Position (x,y) selbst *nicht*
		// mit in die Betrachtungen einbezogen werden.
		// Ausserdem darf bei zellen am rand nicht über den Rand hinausgegriffen
		// werden (diese Zellen haben entsprechend weniger Nachbarn) ...

		// TO DO
		for (int y = 0; y < grid_size; y++)
		{
			for (int x = 0; x < grid_size; x++)
			{
				int living_neighbors = 0;
				for (int y1 = 0; y1 < 3; y1++)
				{
					for (int x1 = 0; x1 < 3; x1++)
					{
						if (x - 1 + x1 < 0 || x - 1 + x1 >= grid_size || y - 1 + y1 < 0 || y - 1 + y1 >= grid_size) //Abfangen der Werte, die ueber dem Rand des arrays sind 
						{
							//Falls man den Rand von Tot auf lebendig aendern will 
							//living_neighbors++;
						}
						else if (x1 == 1 && y1 == 1)
						{
							//sich selber auzer betracht zeihen
						}
						else if (grid[x - 1 + x1][y - 1 + y1] == true) //zaehlen der Lebenden Nachbarn
						{
							living_neighbors++;
						}
					}
				}
				if (grid[x][y] == false && living_neighbors == 3)
					next_grid[x][y] = true;
				else if (living_neighbors < 2 || living_neighbors > 3)
				{
					next_grid[x][y] = false;
				}
				else
					next_grid[x][y] = grid[x][y];
			}
		}

		// Kopiere das naechste Spielfeld in das aktuelle Spielfeld ...

		// TO DO
		for (int y = 0; y < grid_size; y++)
		{
			for (int x = 0; x < grid_size; x++)
			{
				grid[x][y] = next_grid[x][y];
			}
		}

	}
	return 0;
}

void grid_init(bool grid[][grid_size])
{
	int eingabe = -1;
	do {
		cout << "Bitte waehlen Sie die Vorbelegung des Grids aus:" << endl
			<< "0 - Zufall" << endl
			<< "1 - Statisch" << endl
			<< "2 - Blinker" << endl
			<< "3 - Oktagon" << endl
			<< "4 - Gleiter" << endl
			<< "5 - Segler 1 (Light-Weight Spaceship)" << endl
			<< "6 - Segler 2 (Middle-Weight Spaceship)" << endl
			<< "? ";
		cin >> eingabe;
		cin.clear();
		cin.ignore(1000, '\n');
	} while (eingabe < 0 || eingabe > 6);

	if (eingabe == 0)
	{
		// Erstes Grid vorbelegen (per Zufallszahlen) ...

		// TO DO
		for (int y = 0; y < grid_size; y++)
			for (int x = 0; x < grid_size; x++)
				grid[x][y] = gip_random(0, 1);
	}
	else if (eingabe == 1)
	{
		const int pattern_size = 3;
		char pattern[pattern_size][pattern_size] =
		{
			{ '.', '*', '.' },
			{ '*', '.', '*' },
			{ '.', '*', '.' },
		};
		for (int y = 0; y < pattern_size; y++)
			for (int x = 0; x < pattern_size; x++)
				if (pattern[y][x] == '*')
					grid[x][y + 3] = true;
	}
	else if (eingabe == 2)
	{
		const int pattern_size = 3;
		char pattern[pattern_size][pattern_size] =
		{
			{ '.', '*', '.' },
			{ '.', '*', '.' },
			{ '.', '*', '.' },
		};
		for (int y = 0; y < pattern_size; y++)
			for (int x = 0; x < pattern_size; x++)
				if (pattern[y][x] == '*')
					grid[x][y + 3] = true;
	}
	else if (eingabe == 3)
	{
		const int pattern_size = 8;
		char pattern[pattern_size][pattern_size] =
		{
			{ '.', '.', '.', '*', '*', '.', '.', '.' },
			{ '.', '.', '*', '.', '.', '*', '.', '.' },
			{ '.', '*', '.', '.', '.', '.', '*', '.' },
			{ '*', '.', '.', '.', '.', '.', '.', '*' },
			{ '*', '.', '.', '.', '.', '.', '.', '*' },
			{ '.', '*', '.', '.', '.', '.', '*', '.' },
			{ '.', '.', '*', '.', '.', '*', '.', '.' },
			{ '.', '.', '.', '*', '*', '.', '.', '.' },
		};
		for (int y = 0; y < pattern_size; y++)
			for (int x = 0; x < pattern_size; x++)
				if (pattern[y][x] == '*')
					grid[x][y + 1] = true;
	}
	else if (eingabe == 4)
	{
		const int pattern_size = 3;
		char pattern[pattern_size][pattern_size] =
		{
			{ '.', '*', '.' },
			{ '.', '.', '*' },
			{ '*', '*', '*' },
		};
		for (int y = 0; y < pattern_size; y++)
			for (int x = 0; x < pattern_size; x++)
				if (pattern[y][x] == '*')
					grid[x][y + 3] = true;
	}
	else if (eingabe == 5)
	{
		const int pattern_size = 5;
		char pattern[pattern_size][pattern_size] =
		{
			{ '*', '.', '.', '*', '.' },
			{ '.', '.', '.', '.', '*' },
			{ '*', '.', '.', '.', '*' },
			{ '.', '*', '*', '*', '*' },
			{ '.', '.', '.', '.', '.' },
		};
		for (int y = 0; y < pattern_size; y++)
			for (int x = 0; x < pattern_size; x++)
				if (pattern[y][x] == '*')
					grid[x][y + 3] = true;
	}
	else if (eingabe == 6)
	{
		const int pattern_size = 6;
		char pattern[pattern_size][pattern_size] =
		{
			{ '.', '*', '*', '*', '*', '*' },
			{ '*', '.', '.', '.', '.', '*' },
			{ '.', '.', '.', '.', '.', '*' },
			{ '*', '.', '.', '.', '*', '.' },
			{ '.', '.', '*', '.', '.', '.' },
			{ '.', '.', '.', '.', '.', '.' },
		};
		for (int y = 0; y < pattern_size; y++)
			for (int x = 0; x < pattern_size; x++)
				if (pattern[y][x] == '*')
					grid[x][y + 3] = true;
	}
}

