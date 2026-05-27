#include <iostream>
using namespace std;

int suma(int a, int b){
	return (a+b);
}
int resta(int a, int b){
	return (a-b);
}
int multiplicacion(int a, int b){
	return (a*b);
}
int division(int a, int b){
	if (b != 0) { 
		return (a/b);
	} else {
		cout << "Error: No se puede dividir por cero." << endl;
		return 0; 
	}
}

int main(){
	int opcion;
	int num1, num2;
	int resultado; 

	cout << "Elige una operacion:\n";
	cout << "1. Suma\n";
	cout << "2. Resta\n";
	cout << "3. Multiplicacion\n";
	cout << "4. Division\n";
	cin >> opcion;

	cout << "Ingrese el primer numero: ";
	cin >> num1;
	cout << "Ingrese el segundo numero: ";
	cin >> num2;

	switch(opcion){
		case 1:
			resultado = suma(num1, num2);
			cout << "El resultado de la suma es: " << resultado << endl;
			break;
		case 2:
			resultado = resta(num1, num2);
			cout << "El resultado de la resta es: " << resultado << endl;
			break;
		case 3:
			resultado = multiplicacion(num1, num2);
			cout << "El resultado de la multiplicacion es: " << resultado << endl;
			break;
		case 4:
			resultado = division(num1, num2);
			cout << "El resultado de la division es: " << resultado << endl;
			break;
		default:
			cout << "Opcion invalida." << endl;
			break;
	}
	return 0;
}
