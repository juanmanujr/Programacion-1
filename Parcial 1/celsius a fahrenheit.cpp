// convertir grados celcius a fahrenheit
//formula: C * 9/5 + 32

#include <iostream>
using namespace std;

int main(){
	double celsius , fahrenheit;
	
	cout << "Ingrese el grado en celsius: ";
	cin >> celsius; 
	
	fahrenheit= celsius*(9.0/5.0) + 32.0;
	
	cout << "El grado en fahrenheit es: "<< fahrenheit;
	
	return 0;
}
