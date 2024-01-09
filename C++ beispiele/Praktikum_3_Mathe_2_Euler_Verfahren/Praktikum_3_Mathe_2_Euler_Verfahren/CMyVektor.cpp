#include "CMyVektor.h"
#include <iostream>


using namespace std;

// Default Konstruktor
CMyVektor::CMyVektor() {

	// Dimension wird auf 0 gesetzt
	this->dimension = 0;
	// Vektor Typ Double wird erstellt
	this->wert;
}
// Konstruktor für einen Vektor mit bestimmter Dimension 
CMyVektor::CMyVektor(int dimension) {

	// Vektor bekommt die Dimension übergeben
	this->dimension = dimension;
	// Vektor wird mit 0 befüllt
	this->wert.assign(dimension, 0);
}

int CMyVektor::getDimension() {

	return this->dimension;
}

// Bestimmte Komponente des Vektors wird gesetzt auf x
void CMyVektor::setKomponente(int komponente, double x) {

	this->wert[komponente] = x;
}

// Bestimmte Komponente ausgeben
double CMyVektor::getKomponente(int komponente) {

	return this->wert[komponente];
}

// Länge des Vektors (Betrag) => Wurzel aus allen Einträgen zum Quadrat
double CMyVektor::length() {
	double betrag = 0;
	for (int i = 0; i < getDimension(); i++) {
		betrag += this->wert[i] * this->wert[i];
	}

	return sqrt(betrag);

}

// Ausgabe eines Vektors
void CMyVektor::print() {
	cout << "(";
	for (int j = 0; j < wert.capacity(); j++) {
		cout << wert.at(j) << (j == wert.capacity() - 1 ? "" : ", ");
	}
	cout << ")" << endl;
}

CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	// Neuer Vektor, Summe aus a+b
	CMyVektor vektor(a.getDimension());

	// Komponenten des neuen Vektors setzen
	for (int i = 0; i < a.getDimension(); i++) {
		vektor.setKomponente(i, a.getKomponente(i) + b.getKomponente(i));
	}

	return vektor;
}

CMyVektor operator* (double lambda, CMyVektor a) {

	// Neuer Vektor
	CMyVektor vektor(a.getDimension());

	// jeder Eintrag des Vektors wird multipliziert mit lambda
	for (int i = 0; i < a.getDimension(); i++) {
		vektor.setKomponente(i, a.getKomponente(i) * lambda);
	}

	return vektor;

}


CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x)) {

	double h = 1e-8;

	CMyVektor grad(x.getDimension());
	CMyVektor xplush(x.getDimension());
	xplush = x;


	for (int i = 0; i < x.getDimension(); i++) {

		// Komponente wird in temp gespeichert
		double temp = x.getKomponente(i);
		// Addiere h auf die jetzige Komponente und speichere in xplush
		xplush.setKomponente(i, x.getKomponente(i) + h);
		// Formel aus Aufgabenstellung
		double gradKomponente = (funktion(xplush) - funktion(x)) / h;
		// speichere Ergebnis in Vektor grad
		grad.setKomponente(i, gradKomponente);
		// Setze xplush zurück auf alten Wert, der in temp gespeichert ist
		xplush.setKomponente(i, temp);

	}

	return grad;


}

CMyVektor gradientenverfahren(CMyVektor x, double(*funktion)(CMyVektor x), double lambda) {

	CMyVektor x_neu;
	CMyVektor x_test;
	int schritte = 0;


	// Verfahren wird solange durchgeführt, bis 50 Schritte gemacht wurden oder bis ||grad f(x)|| < 10 hoch -5
	while ((schritte != 50) && gradient(x, funktion).length() >= 1e-5) {
		// Ausgabe für Schritt 0
		cout << "Schritt " << schritte << ": " << endl;
		cout << "\tx = "; x.print();
		cout << "\tlambda = " << lambda << endl;
		cout << "\tf(x) = " << funktion(x) << endl;
		CMyVektor a = gradient(x, funktion);
		cout << "\tgrad f(x) = "; a.print();
		cout << "\t||grad f(x)|| = " << gradient(x, funktion).length() << endl << endl;
		x_neu = (lambda * a) + x;
		cout << "\tx_neu = "; x_neu.print();
		cout << "\tf(x_neu) = " << funktion(x_neu) << endl << endl;

		// Falls f(x_neu) > f(x), teste doppelte Schrittweite
		if (funktion(x_neu) > funktion(x)) {
			double lambda2 = lambda * 2;
			x_test = x + (lambda2 * a);
			cout << "\tTest mit doppelter Schrittweite (lambda = " << lambda2 << "):" << endl;
			cout << "\tx_test = "; x_test.print();
			cout << "\tf(x_test) = " << funktion(x_test) << endl;

			// Falls f(x_test) <= f(x_neu)
			if (funktion(x_test) > funktion(x_neu)) {
				cout << "\tverdoppele Schrittweite!" << endl << endl;
				// nimm x_test als neues x
				x = x_test;
				//verdopple lambda
				lambda = lambda2;

			}
			// Ansonsten wird x_neu als neues x genommen und die Schrittweite beibehalten
			else {
				cout << "\tbehalte alte Schrittweite!" << endl << endl;
				x = x_neu;

			}
		}
		// Falls f(x_neu) <= f(x)
		else {
			// Halbiere Schrittweite solange, bis für das x_neu gilt: f(x_neu) > f(x)
			while (funktion(x_neu) <= funktion(x)) {
				lambda = lambda / 2;
				cout << "\thalbiere Schrittweite (lambda = " << lambda << "):" << endl;
				x_neu = x + lambda * a;
				cout << "\tx_neu = "; x_neu.print();
				cout << endl;
				cout << "\tf(x_neu) = " << funktion(x_neu) << endl;
			}
			// x_neu wird als neues x genommen
			x = x_neu;



		}
		// Falls 50 Schritte gemacht wurden
		if (schritte + 1 == 50) {
			cout << "Ende wegen Schrittanzahl = 50 bei" << endl;
			cout << "\tx = "; x.print();
			cout << "\tlambda = " << lambda << endl;
			cout << "\tf(x) = " << funktion(x) << endl;
			x_neu = gradient(x, funktion);
			cout << "\tgrad f(x) = "; x_neu.print();
			cout << "\t||grad f(x)|| = " << x_neu.length() << endl << endl;
		}
		// Falls ||grad f(x)|| < 10 hoch -5
		if (gradient(x, funktion).length() < 1e-5) {
			cout << "Ende wegen ||grad f(x) || < 1e-5" << endl;
			cout << "\tx = "; x.print();
			cout << "\tlambda = " << lambda << endl;
			cout << "\tf(x) = " << funktion(x) << endl;
			x_neu = gradient(x, funktion);
			cout << "\tgrad f(x) = "; x_neu.print();
			cout << "\t||grad f(x)|| = " << x_neu.length() << endl << endl;

		}


		schritte++;
		cout << endl;

	}
	return x;
}

