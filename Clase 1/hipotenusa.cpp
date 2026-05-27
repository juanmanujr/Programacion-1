#include <iostream>
#include <cmath>
using namespace std; 
int main(){
	int c1, c2, h;
	cout << "Ingrese el cateto 1: \n";
	cin >> c1;
	cout << "Ingrese el cateto 2: \n";
	cin >> c2;
	h=(c1*c1 + c2*c2);
	cout << "La hipotenusa es: " << sqrt(h);
	return 0; 
}
