//6. Función que calcula el factorial de un número
#include <iostream>
using namespace std;

int factorial(int n){
	int resultado = 1;
	for (int i= 1; i<=n; i++){
		resultado= i*resultado;
	}
	return resultado;
}
int main(){
	int numero;
	cout << "Ingrese el numero: ";
	cin >> numero;
	
	if(numero>=0){
		cout << "El factorial del numero es: " << factorial(numero);
	}else{
	cout << "El factorial no esta definido para numeros negativos"	;
		
	}

	
	
	
	return 0;
}
