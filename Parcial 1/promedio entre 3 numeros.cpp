//- Calcular el promedio de 3 numeros
#include <iostream>
using namespace std;
int main(){
	double num1, num2, num3, promedio; 
	
	cout << "Ingrese un numero: ";
	cin >> num1;
	
	cout << "Ingrese un numero: ";
	cin >> num2;
	
	cout << "Ingrese un numero: ";
	cin >> num3;
	
	promedio= (num1+num2+num3)/3;
	
	cout << "El promedio es: "  << promedio; 
	
	return 0; 
}
