//- Escribe una funcion areaCirculo que reciba el radio y retorne el área del circulo. Usa PI=3.1416.
#include <iostream>
using namespace std;
double areaCirculo(double radio ){
	return radio*radio*3.1416;
	
}

int main(){
	double r;
	cout << "Ingrese el radio: ";
	cin >> r;
	cout << "El area del circulo es: " <<areaCirculo(r);
	
	return 0;
}
