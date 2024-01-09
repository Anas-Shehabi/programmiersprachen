#define CATCH_CONFIG_RUNNER

#include "catch.h"

#include <iostream>
#include "Graph.h"

using namespace std;

int main(int argc, char **argv)
{
    Catch::Session().run();
    Graph *adsGraph = new Graph;
    adsGraph->init("graph1.txt");
    int input;
    do {
        do 
		{
            cout << "\nWorking on Grphs. Please choose:\n"
                    "1) Graph einlesen\n"
                    "2) Tiefensuche\n"
                    "3) Breitensuche\n"
                    "4) Prim\n"
                    "5) Kruskal\n"
                    "6) Print Graph\n"
                    "0 zum beenden\n"
                    "?> ";
            cin >> input;
        } while (input > 6 || input < 0);
        if (input == 1) {
            delete adsGraph;
            adsGraph = new Graph;
            string path = "graph";
            char pathRest;
            cout << "graph 1 , 2 or 3 ? ";
            cin.ignore();
            cin >> pathRest;
            path = path + pathRest + ".txt";
            cout << path << endl;
            adsGraph->init(path);
        }
        if (input == 2) 
		{
            int key;
            cout << "Start Key eingeben : ";
            cin.ignore();
            cin >> key;
            adsGraph->depthSearchRek(key) ? cout << "Alle Knoten sind verbunden" << endl
                                          : cout << "Alle Knoten konnten nicht erreicht werden!" << endl;
        }
        if (input == 3) 
		{
            int key;
            cout << "Start Key eingeben : ";
            cin.ignore();
            cin >> key;
            adsGraph->breadthSearchIter(key) ? cout << "Alle Knoten sind verbunden" << endl
                                             : cout << "Alle Knoten konnten nicht erreicht werden!" << endl;
        }
        if (input == 4) {
            int key;
            cout << "Start Key eingeben : ";
            cin.ignore();
            cin >> key;
            adsGraph->prim(key);

        }
        if (input == 5) {
            adsGraph->kruskal();
        }
        if (input == 6) {
            adsGraph->printAll();
        }
        if (input == 0) {
            break;
        }

    } while (input != 0);
	system("pause");
    return 0;
}