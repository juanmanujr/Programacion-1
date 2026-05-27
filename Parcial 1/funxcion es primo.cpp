//- Crea una funcion esPrimo que determine si un numero es primo. (Ejercicio que puede que si puede
// que no salga en el examen.)
#include <iostream>
using namespace std;

bool esPrimo(int n){
	if (n<=1) return false;// 0 y 1 no son primos
	
	for (int i=2; i<n; i++){
	if(n%i==0){
		return false; // si tiene otro divisor no es primo
	}	
	
	}
	return true;// si no se encontro ningun divisor es primo
}

int main(){
	int numero;
	cout << "Ingreese un numero: ";
	cin >> numero;
	if (esPrimo(numero))
	cout << numero << " es primo ";
	else
	cout << numero << " no es primo";
	
	return 0;
}
