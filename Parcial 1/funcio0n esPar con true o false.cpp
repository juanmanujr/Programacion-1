//- Escribe una función esPar que reciba un número entero y retorne true si es par, 
//o false si es impar.
#include <iostream>

using namespace std;
	bool esPar(int numero){
	return 	(numero%2==0);
	}
	
int main(){
	int n;
	cout << "Ingrese un numero: ";
	cin >> n;
	if(esPar(n)){
		cout << n << " es par ";
	}else{
		cout << n << " es impar ";
	}
//	cout << n << (esPar(n) ? " es par" : " es impar");
	return  0;
}

