//Escriba un programa que lea la nota final de cuatro alumnos y la calcule la nota final
// media de los cuatro alumnos
#include <iostream>
using namespace std;

int main(){
	int a, b, c, d, media;
	
	cout << "Ingrese su nota: ";
	cin >> a;
	cout << "Ingrese su nota: ";
	cin >> b;
	cout << "Ingrese su nota: ";
	cin >> c;
	cout << "Ingrese su nota: ";
	cin >> d;
	media = (a+b+c+d)/4;
	cout << "Su media es: " << media;
	
	return 0;
}

