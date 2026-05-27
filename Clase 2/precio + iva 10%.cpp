//Realice un programe en c++ que calcule
// el precio de un objeto
// con el impuesto al valor agregado (IVA) 10%
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
int main (){
	int precio, iva, total;
	cout<< "Ingrese el valor del producto\n";
	cin >> precio; 
	total=precio*0.10+precio;
	cout << "Precio con IVA:\n" <<total;
	
	
	return 0;
}
