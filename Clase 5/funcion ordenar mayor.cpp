//- Realizar un programa en c++ que reciba dos variables (x, y) 
//y ordene cual de los valores introducidos es el mayor

#include <iostream>
using namespace std;
void ordenar(int x, int y){
	if(x<y){
		cout << "El mayor es: " << y;
	}else if (y<x){
		cout << "El mayor es: " << x;
	}else if( x==y){
		cout << x << " y " << y << " son iguales "  ;
	}	
}


int main(){
	int x, y;
	cout << "Ingrese un numero: ";
	cin >> x;
	cout << "Ingrese un numero: ";
	cin >> y;
	ordenar(x, y);
	return 0; 
}
