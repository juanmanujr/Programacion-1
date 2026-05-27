//Realizar un programa en c++ que reciba dos variables (x, y) y ordene 
//cual de los valores introducidos es el mayor 
#include <iostream>
using namespace std;
int main(){
	int x, y;
	cout << "Ingrese un numero: ";
	cin >> x;
	cout << "Ingrese un numero: ";
	cin >> y; 
	if (x>y){
		cout << "El mayor es: " <<x;
	}else if (x<y){
	cout <<	"El mayor es: " <<y;
	}else if (x==y){
		cout << "Son iguales " <<x <<" y " << y;
		
	}
	
	return 0;
}
