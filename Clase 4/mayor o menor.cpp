//Realizar un programa en c++ que reciba dos variables (x, y) y 
//ordene cual de los valores introducidos es el mayor 
#include <iostream>
using namespace std; 
int main(){
	int x, y; 
	int menor, mayor;
	
	cout << "Ingrese un numero: ";
	cin >> x;
	cout << "Ingrese un numero: ";
	cin>> y;
	
	if(x==y){
		cout << "\nSon iguales";
		
	}
	
	if(x<y){
		cout<< "El numero mayor es: " << y;
		mayor=y;
	}else if (x<y){
		cout << "El numero menor es: " << x;
		menor = x;
	}
	
	cout << "\nOrdenado de mayor a menor: " << menor << " , " <<mayor;
	
	return 0;
}
