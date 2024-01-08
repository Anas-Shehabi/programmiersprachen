#include"CMyMatrix.h"
#include<math.h>
using namespace std;

CMyMatrix::CMyMatrix(int zeile, int spalte)
{
	set_zeile(zeile);
	set_spalte(spalte);
	this->Matrix = new double*[zeile];
	for (int i = 0; i < zeile; i++)
		Matrix[i] = new double[spalte];
}
void CMyMatrix::set_Komponente(int zeile, int spalte, double Komponente)
{
	this->Matrix[zeile][spalte] = Komponente;
}
double CMyMatrix::get_Komponente(int zeile, int spalte)
{
	return Matrix[zeile][spalte];
}
CMyMatrix CMyMatrix::invers()
{
	double det = 1 / (this->get_Komponente(0, 0)*this->get_Komponente(1, 1) - this->get_Komponente(0, 1)*this->get_Komponente(1, 0));
	if (this->zeile == 2 && this->spalte == 2 && det != 0)
	{
		CMyMatrix MAX(2, 2);
		MAX.set_Komponente(0, 0, det*get_Komponente(1, 1));
		MAX.set_Komponente(1, 1, det*get_Komponente(0, 0));
		MAX.set_Komponente(0, 1, (-1)*det*get_Komponente(0, 1));
		MAX.set_Komponente(1, 0, (-1)*det*get_Komponente(1, 0));
		return MAX;
	}
	// Ansonsten Fehler meldung
}
CMyVektor operator*(CMyMatrix A, CMyVektor x)
{
	CMyVektor v(A.get_zeile());
	if (A.get_spalte() == x.get_deminision())
	{
		double d;
		for (int j = 0; j < A.get_spalte(); j++)
		{
			d = 0;
			for (int k = 0; k < A.get_zeile(); k++)
				d += A.get_Komponente(j, k)*x.get_komponente(k);
			v.set_komponente(j, d);
		}
		return v;
	}
	//sonst Fehler
}
