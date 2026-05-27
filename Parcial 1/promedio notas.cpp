//Calcule la media de tres notas de un alumno, de la materia de Programacion.
// Las notas van desde el 1 al 5 y se deben de ingresar 3 notas.

#include <iostream>
using namespace std;
int main(){
	int a,b, c, promedio; 
	cout << "Ingrese su nota: ";
	cin >> a;
	cout << "Ingrese su nota: ";
	cin >> b;
	cout << "Ingrese su nota: ";
	cin >> c;
	promedio = (a+b+c)/3;
	cout << "Su promedio es: " <<promedio;
	
	return 0;
}

