//Mini calculadora con funciones, suma, resta, multiplicacion, division,que el usuario elija la operación con un menu
#include <iostream>
using namespace std;

int suma(int a, int b){
	return a+b;
}

int resta(int a, int b){
	return a-b;
}

int multiplicacion(int a, int b){
	return a*b;
}
int division(int a, int b){
	if(b!=0){
	return a/b;
	}else{
		cout << "No se admite la division por 0";
		return 0;
	}
}

int main(){
	int num1, num2 , operacion, resultado;
	cout << "Ingrese un numero: ";
	cin >> num1;
	cout << "Ingrese un numero: ";
	cin >> num2;
	cout << "\nElige una operacion:";
	cout << "\n1: Suma: ";
	cout << "\n2: Resta: ";
	cout << "\n3: Multiplicacion: ";
	cout << "\n4: Division: \n";
	cin >> operacion;
	
	switch (operacion){
	
	case 1: 
		resultado= suma(num1, num2);
		cout << "El resultado es: " << resultado;
		break;
	case 2:
		resultado= resta(num1, num2);
		cout << "El resultado es: " << resultado;
		break;
	case 3:
		resultado= multiplicacion(num1, num2);
		cout << "El resultado es: " << resultado;
		break;
	case 4: 
		resultado= division(num1, num2);
		cout << "El resultado es: " << resultado;
		break;
		default:
			cout: "Operacion no valida";
}
	return 0;
}
