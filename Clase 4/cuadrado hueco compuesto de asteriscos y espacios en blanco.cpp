//4.25 Escriba un programa que pida al usuario que introduzca el 
//tamaño del lado de un cuadrado y que muestre un cuadrado
//hueco de ese tamaño, compuesto de asteriscos y espacios en blanco. 
//Su programa debe funcionar con cuadrados que tengan
//lados de todas las longitudes entre 1 y 20. Por ejemplo,
// si su programa lee un tamaño de 5, debe imprimir
#include <iostream>
using namespace std;
int main(){
	int tamano, i;
	cout << "Introduzca el tama�o de un cuadrado (entre 1 y 20): ";
	cin >> tamano;
	if(tamano<21){
		for (i=0; i<tamano; i++){
			cout << "*";
			
		}
		
	}
	return 0;
}
