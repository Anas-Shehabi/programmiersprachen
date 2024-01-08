#pragma once
#include"CMyVektor.h"
class CMyMatrix
{
private:
	int zeile, spalte;
	double **Matrix;
public:
	CMyMatrix() {}
	CMyMatrix(int, int);
	int get_zeile() { return zeile; }
	int get_spalte() { return spalte; }
	void set_zeile(int Dimenision) { zeile = Dimenision; }
	void set_spalte(int Dimenision) { spalte = Dimenision; }
	void set_Komponente(int, int, double);
	double get_Komponente(int, int);
	CMyMatrix invers();
	friend CMyVektor operator*(CMyMatrix A, CMyVektor x);
};


