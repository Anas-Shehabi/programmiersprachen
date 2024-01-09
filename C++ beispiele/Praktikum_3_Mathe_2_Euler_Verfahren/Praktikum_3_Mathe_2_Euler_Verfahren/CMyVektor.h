#pragma once
#pragma once
#include <vector>
using namespace std;

class CMyVektor {

private:
	int dimension;
	vector<double> wert;

public:
	CMyVektor();

	// Vektor einer bestimmten Dimension anlegen
	CMyVektor(int dimension);

	// Dimension eines Vektors ausgeben
	int getDimension();

	// eine bestimmte Komponente des Vektors setzen
	void setKomponente(int komponente, double x);

	// eine bestimmte Komponente des Vektors ausgeben
	double getKomponente(int komponente);

	// Länge des Vektor
	double length();

	// Ausgabe von Vektor
	void print();


};
// überladene Operator-Funktionen
// Vektor-Addition
CMyVektor operator+ (CMyVektor a, CMyVektor b);
// skalara Multiplikation
CMyVektor operator* (double lambda, CMyVektor a);

// Berechnet Gradient, der man im ersten Parameter Stelle x und im zweiten die Funktion f als Funktionspointer übergibt
CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x));

// Gradientenverfahren, der man im ersten Parameter die Startstelle, im zweiten die Funktion f als Funktionspointer
// im dritten die Schrittweite lambda, in dem Fall mit default-Wert 1.0
CMyVektor gradientenverfahren(CMyVektor x, double(*funktion)(CMyVektor x), double lambda = 1.0);

