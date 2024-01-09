#include "C_DGLSolver.h"
#include "CMyVektor.h"
#include <iostream>
using namespace std;

// Konstruktor für 1.Ordnung
C_DGLSolver::C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x)) : hoehereOrdnung(false), f_DGL_System(f_DGL_System) {}
// Konstruktor für höhere Ordnung
C_DGLSolver::C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVektor y, double x)) : hoehereOrdnung(true), f_DGL_nterOrdnung(f_DGL_nterOrdnung) {}

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x) {

	CMyVektor ergebnis(y.getDimension());

	// es wird eine DGL höherer Ordnung übergeben, eine Transformation in ein DGL-System durchgeführt und die rechte Seite ausgegeben
	if (hoehereOrdnung) {
		for (int i = 0; i < y.getDimension() - 1; i++) {
			// Fülle Vektor bis vorletzte Stelle
			ergebnis.setKomponente(i, y.getKomponente(i + 1));
		}
		// Schreibe ausgewertetes Ergebnis an letzte Stelle 
		ergebnis.setKomponente(y.getDimension() - 1, f_DGL_nterOrdnung(y, x));
	}
	// Funktion wird für ein DGL-System übergeben und an der Stelle (y;x) ausgewertet = y'
	else {
		ergebnis = f_DGL_System(y, x);
	}

	return ergebnis;
}

CMyVektor C_DGLSolver::euler_verfahren(double x_start, double x_end, int anzahl_schritte, CMyVektor y_start) {
	// h
	double schrittweite = (x_end - x_start) / anzahl_schritte;
	CMyVektor y_ableitung = ableitungen(y_start, x_start);

	// Ausgabe für Schritt 0
	if (ausgaben) {
		cout << "Schritt 0: " << endl
			<< "\t x = " << x_start << endl
			<< "\t y = "; y_start.print(); cout << endl
			<< "\t y' = "; y_ableitung.print(); cout << endl << endl;
	}
	// Solange bis Schritte erreicht sind
	for (double i = x_start, j = 1; i < x_end && j <= anzahl_schritte; i += schrittweite, j++) {

		// y(x) = y(xalt) + h * y'(y(xalt))
		y_start = y_start + (schrittweite*y_ableitung);
		// x1 = x0 + h, x2 = x1 + 2h ...
		x_start += schrittweite;

		// Rechne y' aus
		y_ableitung = ableitungen(y_start, x_start);

		// Anzahl Schritte erreicht
		if (ausgaben && j == anzahl_schritte) {
			cout << "Ende bei " << endl
				<< "\t x = " << x_start << endl
				<< "\t y = "; y_start.print(); cout << endl << endl;
		}
		// Anzahl Schritte nicht erreicht
		else if (ausgaben) {
			cout << "Schritt " << j << ":" << endl
				<< "\t x = " << x_start << endl
				<< "\t y = "; y_start.print(); cout << endl
				<< "\t y' = "; y_ableitung.print(); cout << endl << endl;
		}

	}

	return y_start;
}

CMyVektor C_DGLSolver::heun_verfahren(double x_start, double x_end, int anzahl_schritte, CMyVektor y_start) {

	double schrittweite = (x_end - x_start) / anzahl_schritte;
	// y' ausrechnen => y' original
	CMyVektor y_ableitung = ableitungen(y_start, x_start);
	// y(x) = y(xalt) + h * y'(y(xalt))
	CMyVektor y_test = y_start + (schrittweite * y_ableitung);
	// neues y' ausrechnen
	CMyVektor y_test_ableitung = ableitungen(y_test, x_start + schrittweite);
	// mittlere Steigung = s
	CMyVektor y_mittel = 0.5 *(y_ableitung + y_test_ableitung);

	if (ausgaben) {
		cout << "Schritt 0: " << endl
			<< "\t x = " << x_start << endl
			<< "\t y = "; y_start.print(); cout << endl
			<< "\t y'_orig = "; y_ableitung.print(); cout << endl << endl
			<< "\t y_Test = "; y_test.print(); cout << endl
			<< "\t y'_Test = "; y_test_ableitung.print(); cout << endl << endl
			<< "\t y'_Mittel = "; y_mittel.print(); cout << endl << endl << endl;
	}

	for (double i = x_start, j = 1; i < x_end && j <= anzahl_schritte; i += schrittweite, j++) {
		// y(xneu) = y(xalt) + h * s
		y_start = y_start + (schrittweite*y_mittel);
		x_start += schrittweite;

		y_ableitung = ableitungen(y_start, x_start);
		y_test = y_start + (schrittweite * y_ableitung);
		y_test_ableitung = ableitungen(y_test, x_start + schrittweite);
		y_mittel = 0.5 * (y_ableitung + y_test_ableitung);

		if (ausgaben && j == anzahl_schritte) {
			cout << "Ende bei " << endl
				<< "\t x = " << x_start << endl
				<< "\t y = "; y_start.print(); cout << endl << endl;
		}
		else if (ausgaben) {
			cout << "Schritt " << j << ":" << endl
				<< "\t x = " << x_start << endl
				<< "\t y = "; y_start.print(); cout << endl
				<< "\t y'_orig = "; y_ableitung.print(); cout << endl << endl
				<< "\t y_Test = "; y_test.print(); cout << endl
				<< "\t y'_Test = "; y_test_ableitung.print(); cout << endl << endl
				<< "\t y'_Mittel = "; y_mittel.print(); cout << endl << endl << endl;
		}

	}

	return y_start;
}
