/*Escribe un programa en c++ que lea la entrada estandar del precio de un producto y muestre en la salida estándar el precio del producto al palicarle el IVA 
Entrada caso de prueba: Precio: 100
Salida caso de prueba: Precio con iva: 110 se supone un IVA del 10%*/
#include <iostream>
/*using std::cout;
using std::cin; 
using std::endl;*/
using namespace std;
int main(){
	int precio=0; 
	int pf=0;
	const double iva=0.10;
	cout << "Ingrese el precio: ";
	cin >> precio;
	pf=(precio*iva) + precio;
	cout << "El precio final es: " << pf;
	return 0;
}
