//Escribe una función recursiva que devuelva el N-ésimo número de Fibonacci.

#include <iostream>
using namespace std;

//funcion recursiva para calcular el enesimo numero de fibonnaci
int fibonacci(int n){
	if (n==0) return 0; // caso base 1
	if (n==1) return 1; // caso base 2
	return fibonacci(n-1) + fibonacci(n-2); //llamada recursiva
}

int main(){
	int n;
	cout << "Ingrese el numero de la posicion en la sucesion de fibonacci: ";
	cin >> n;
	
	cout << "El numero en la posicion " << n << " es: " << fibonacci(n);
	
	return 0;
}
