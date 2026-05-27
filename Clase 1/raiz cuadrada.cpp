#include <iostream>
#include <cmath>
using namespace std;

int main(){
	double x, r; 
	cout << "Introduce un numero: ";
	cin >> x; 
	r=pow(x, 3) +4;
	cout << "x^3 + 4 vale: " << r;
	cout << "\nSu raiz cuadrada vale:  " << sqrt (x);
	return 0;
}
