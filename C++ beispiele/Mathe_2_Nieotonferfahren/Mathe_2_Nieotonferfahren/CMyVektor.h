#pragma once
#pragma once
#include<math.h>

class CMyVektor {
	int Deminision;
	double* Komponente = nullptr;
public:
	CMyVektor();
	CMyVektor(int n);
	void set_komponente(int n, double komponente);
	double get_komponente(int n);
	void set_deminision(int deminision);
	int get_deminision();
	double laenge();

	friend CMyVektor operator+ (CMyVektor a, CMyVektor b);
	friend CMyVektor operator*(double lambda, CMyVektor a);
	friend	CMyVektor operator*(CMyVektor a, double lambda);
};

//CMyVektor operator+(CMyVektor a, CMyVektor b);
//CMyVektor operator*(double lambda, CMyVektor a);
//CMyVektor operator*(CMyVektor a, double lambda);
//
