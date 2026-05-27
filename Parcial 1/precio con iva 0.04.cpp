//- Escribe un programa en c++ que lea la entrada estandar del precio 
//de un producto y muestre en la salida estándar el precio del producto al palicarle el IVA 
#include <iostream>
using namespace std;

int main(){
	int precio;
	
	cout << "Ingrese el precio del producto: ";
	cin >> precio;
	
	precio= precio + (precio*0.04);
	
	cout << "El precio con iva incluido es: " << precio;
	
	return 0;
}
