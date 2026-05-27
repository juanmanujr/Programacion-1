//Realice un progrema en c++ que calcule el area de un triangulo 
#include <iostream>
using namespace std;
int main(){
	double area, base, altura;
	
	cout << "Ingrese la base del triangulo: ";
	cin >> base;
	cout << "Ingrese la altura del triangulo: ";
	cin >> altura;
	
	area= (base*altura)/2;
	cout << "El area del triangulo es: " << area;
	
	
	return 0;
}
