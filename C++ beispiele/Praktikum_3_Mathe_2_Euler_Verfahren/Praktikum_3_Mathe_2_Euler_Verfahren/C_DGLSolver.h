#pragma once
#include "CMyVektor.h"

class C_DGLSolver {

private:
	// rechte Seite des DGL-Systems
	CMyVektor(*f_DGL_System)(CMyVektor y, double x);

	// DGL höherer Ordnung
	double(*f_DGL_nterOrdnung)(CMyVektor y, double x);

	// DGL-System oder DGL höherer Ordnung
	bool hoehereOrdnung;

	// Transformation in erste Ordnung
	CMyVektor ableitungen(CMyVektor y, double x);

public:
	C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x));
	C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVektor y, double x));

	bool ausgaben = true;
	CMyVektor euler_verfahren(double x_start, double x_end, int anzahl_schritte, CMyVektor y_start);
	CMyVektor heun_verfahren(double x_start, double x_end, int anzahl_schritte, CMyVektor y_start);

};
