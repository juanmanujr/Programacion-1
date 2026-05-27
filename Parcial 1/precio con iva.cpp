//Realice un programe en c++ que calcule el precio de un objeto con el 
//impuesto al valor agregado (IVA) 10%

#include <iostream>
using namespace std;
int main(){
	double precio ;
	
	cout << "Ingrese el precio del producto: ";
	cin >> precio;
	
	precio= precio + (precio*(0.1));
	//o tambien 	precio= precio + (precio*(10.0/100.0));
	
	cout << "El precio con iva del 10% es: " << precio;
	
	return 0;
}
