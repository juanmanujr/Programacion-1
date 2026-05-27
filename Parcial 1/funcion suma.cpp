//- Crea una función llamada suma que reciba dos numeros enteros y retorne su suma
#include <iostream>
using namespace std;
	int suma (int num1, int num2){
		return num1+num2;	
	}
int main(){
	int a, b;
	cout << "Ingrese un numero: ";
	cin >> a;
	cout << "Ingrese un numero: ";
	cin >> b;
	suma(a, b);
	cout << "La suma es: " << suma(a, b);

	return 0;
}
