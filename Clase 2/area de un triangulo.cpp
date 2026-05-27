//Realice un progrema en c++ que calcule 
//el area de un triangulo 

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main(){
	double b, h, a;
	cout << "Ingrese la base del triangulo: ";
	cin>>b;
	
	cout << "Ingrese la altura del triangulo: ";
	cin>>h;
	
	a=(b*h)/2;
	
	cout << "El area es: " <<a;
	
	
	return 0;
}
