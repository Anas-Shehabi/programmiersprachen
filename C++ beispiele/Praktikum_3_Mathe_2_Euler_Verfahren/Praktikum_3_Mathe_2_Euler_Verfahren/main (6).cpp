#include "CMyVektor.h"
#include "C_DGLSolver.h"
#include <iostream>
using namespace std;

CMyVektor y1(CMyVektor y, double x)
{
	if (y.getDimension() != 2) 
	{
		cout << "Vektor passt nicht zur Funktion!" << endl;
	}

	double y1 = y.getKomponente(0);
	double y2 = y.getKomponente(1);

	CMyVektor ergebnis(2);
	ergebnis.setKomponente(0, 2 * y2 - x * y1);
	ergebnis.setKomponente(1, y1 * y2 - 2 * x*x*x);

	return ergebnis;
}

double y2(CMyVektor y, double x) {
	if (y.getDimension() != 3) {
		cout << "Vektor passt nicht zur Funktion!" << endl;
	}

	double y0 = y.getKomponente(0);
	double y1 = y.getKomponente(1);
	double y2 = y.getKomponente(2);

	return (2 * x*y1*y2) + (2 * y0*y0*y1);
}

int main() {
	double start = 0;
	double end = 2;
	int schritte = 100;

	// DGL-System: y1
	//C_DGLSolver solver(y1);

	////y1(0) = 0, y2(0) = 1;
	//CMyVektor y(2);
	//y.setKomponente(0, 0);
	//y.setKomponente(1, 1);

	// DGL dritter Ordnung: y2
	C_DGLSolver solver(y2);

	// y(1) = 1, y'(1) = -1, y''(1) = 2 => ystart
	CMyVektor y2(3);
	y2.setKomponente(0, 1);
	y2.setKomponente(1, -1);
	y2.setKomponente(2, 2);
	solver.ausgaben = false;

	//solver.euler_verfahren(start, end, schritte, y);
	//solver.heun_verfahren(start, end, schritte, y);



	// Berechnung der Abweichung von Euler- und Heun-Verfahren vom Original
	start = 1;
	if (!solver.ausgaben) {
		for (int i = 10; i < 100000; i *= 10) {
			cout << "Abweichung bei Euler bei " << i << " Schritten: " << solver.euler_verfahren(start, end, i, y2).getKomponente(0) - 0.5 << endl;
			cout << "Abweichung bei Heun bei " << i << " Schritten: " << solver.heun_verfahren(start, end, i, y2).getKomponente(0) - 0.5 << endl;
		}
	}

	system("PAUSE");
	return 0;

}