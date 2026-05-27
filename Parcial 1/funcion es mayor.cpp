//Crea una funcion "mayor" que reciba dos numeros y retorne el mayor de ellos.
#include <iostream>
using namespace std;
int esMayor(int num1, int num2){
	return (num1>num2 ? num1 : num2);
}

int main(){
	int a, b;
	cout << "Ingrese un numero: ";
	cin >> a;
	cout << "Ingrese un numero: ";
	cin >> b;
	
	cout << "Es mayor: " << esMayor(a, b);
	
	
	return 0;
}


