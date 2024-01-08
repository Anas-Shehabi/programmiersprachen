#include<iostream>
#include<math.h>
#include"CMyMatrix.h"
#include"CMyVektor.h"
using namespace std;

CMyVektor funktion(CMyVektor _x)
{
	double x, y;
	x = _x.get_komponente(1);
	y = _x.get_komponente(2);
	CMyVektor v(2);
	v.set_komponente(1,pow(x,3)*pow(y,3)-2*y); //x3*y3 − 2y
	v.set_komponente(2, x-2);// x − 2
	return v;
}

CMyMatrix jacobi(CMyVektor x, CMyVektor(*Funktion)(CMyVektor x))
{
	CMyMatrix max(2, 2);
	CMyVektor v2(x.get_deminision());
	for (int i = 1; i <= v2.get_deminision(); i++)
		v2.set_komponente(i, x.get_komponente(i));
	double h = pow(10, -4);
	for (int i = 1; i <= v2.get_deminision(); i++)
	{
		for (int j = 1; j <= 2; j++)
		{
			v2.set_komponente(j, v2.get_komponente(j) + h);
			max.set_Komponente(i - 1, j - 1, ((funktion(v2).get_komponente(i) - funktion(x).get_komponente(i)) / h));
			v2.set_komponente(j, v2.get_komponente(j) - h);
		}
	}
	return max;
}

CMyVektor newtonVerfahren(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	int counter = 0;
	CMyVektor x1(2),d_x(2),x0(2);
	x0 = x;
	CMyMatrix max(2, 2);
	 while (funktion(x1).laenge() >= pow(10, -5) && counter < 50)
	{
		max = jacobi(x0, funktion);
		cout << "Schritt " << counter << ":" << endl;
		cout << "\t x = ( " << x0.get_komponente(1) << "; " << x0.get_komponente(2) << " )" << endl;
		cout << "\t f(x) = ( " << funktion(x0).get_komponente(1) << "; " << funktion(x0).get_komponente(2) << " )" << endl;
		cout << "\t f'(x) = " << endl
			<< "\t \t ( " << max.get_Komponente(0, 0) << "; " << max.get_Komponente(0, 1) << endl
			<< "\t \t  " << max.get_Komponente(1, 0) << "; " << max.get_Komponente(1, 1) << " )" << endl;
		cout << "\t (f'(x))^(-1) =" << endl
			<< "\t \t ( " << max.invers().get_Komponente(0, 0) << "; " << max.invers().get_Komponente(0, 1) << endl
			<< "\t \t " << max.invers().get_Komponente(1, 0) << "; " << max.invers().get_Komponente(1, 1) << " )" << endl;
		CMyVektor funk = -1 * funktion(x0);
		max = max.invers();
		d_x.set_komponente(1, max.get_Komponente(0, 0) * funk.get_komponente(1) + max.get_Komponente(0, 1) * funk.get_komponente(2));
		d_x.set_komponente(2, max.get_Komponente(1, 0) * funk.get_komponente(1) + max.get_Komponente(1, 1)* funk.get_komponente(2));
	//	d_x = max * funk;
		cout << "\t dx = ( " << d_x.get_komponente(1) << "; " << d_x.get_komponente(2) << " )" << endl;
		cout << "\t ||f(x)|| = " << funktion(x0).laenge() << endl;
		x1 = d_x + x0;
		x0 = x1;
		counter++;
	}
	 if (funktion(x1).laenge() < pow(10, -5))
	 {
		 cout << "\n Ende wegen ||f(x)||<1e-5 bei " << endl;
		 cout << "\t x = ( " << x0.get_komponente(1) << "; " << x0.get_komponente(2) << " )" << endl;
		 cout << "\t f(x) = ( " << funktion(x0).get_komponente(1) << "; " << funktion(x0).get_komponente(2) << " )" << endl;
		 cout << "\t ||f(x)|| = " << funktion(x0).laenge() << endl;
	 }
	return x1;
}
int main()
{
	CMyVektor v(2),x(2);
	x.set_komponente(1, 1);
	x.set_komponente(2, 1);
	v = newtonVerfahren(x, funktion);
	system("pause");
	return 0;
}