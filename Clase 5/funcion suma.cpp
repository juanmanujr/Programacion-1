//Crea una funcion llamada suma que reciba dos numeros enteros y retorne su suma
#include <iostream>
using namespace std;

int suma(int &a, int &b){
	return (a+b);
	
}


int main(){
	int a, b; 
	cout << "Ingrese un numero: ";
	cin >> a;
	cout << "Ingrese un numero: ";
	cin >> b;
	
	cout << "La suma es: " << suma(a,b);
	
	return 0; 
}
