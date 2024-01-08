#include"CMyVektor.h"

CMyVektor::CMyVektor()
{
	Deminision = 2;
	Komponente = new double[Deminision];
}

CMyVektor::CMyVektor(int n)
{
	this->Deminision = n;
	Komponente = new double[n];
}

void CMyVektor::set_komponente(int n, double _komponente)
{
	if (n <= this->Deminision)
		this->Komponente[n - 1] = _komponente;
}

double CMyVektor::get_komponente(int n)
{
	if (n <= Deminision)
		return this->Komponente[n - 1];
	else
		return 0;
}

void CMyVektor::set_deminision(int _deminision)
{
	this->Deminision = _deminision;
	Komponente = new double[_deminision];
}

int CMyVektor::get_deminision()
{
	return this->Deminision;
}

double CMyVektor::laenge()
{
	double _pow = 0;
	for (int i = 0; i < Deminision; i++)
		_pow += pow(Komponente[i], 2);
	return sqrt(_pow);
}

CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	CMyVektor c(a.get_deminision());
	for (int i = 1; i <= c.get_deminision(); i++)
		c.set_komponente(i, a.get_komponente(i) + b.get_komponente(i));
	return c;
}

CMyVektor operator*(double lambda, CMyVektor a)
{
	CMyVektor v(a.Deminision);
	for (int i = 1; i <= v.Deminision; i++)
		v.set_komponente(i, lambda * a.get_komponente(i));
	return v;
}

CMyVektor operator*(CMyVektor a, double lambda)
{
	CMyVektor v(a.Deminision);
	for (int i = 1; i <= v.Deminision; i++)
		v.set_komponente(i, lambda * a.get_komponente(i));
	return v;
}

