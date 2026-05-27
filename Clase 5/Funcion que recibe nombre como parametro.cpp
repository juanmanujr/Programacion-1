#include <iostream>
using namespace std;

void saludar (string nombre){
	cout << "Hola," << nombre << "!Bienvenido a C++" <<endl;
}
int main(){
	string nombre;
	cout << "Ingrese su nombre: ";
	cin >> nombre;
	saludar(nombre);
	return 0;
}

