//Escribe una funcion areaCirculo que reciba el radio y retorne el 
//área del circulo. Usa PI=3.1416.
#include <iostream>
using namespace std; 
const float PI = 3.1416;
float areaCirculo(float radio){
	return PI*radio*radio;
}

int main(){
	int radio;
	cout << "Ingrese el radio: ";
	cin >> radio;
	cout << "El area del circulo es: " << areaCirculo (radio) ;
	
	return 0; 
}
