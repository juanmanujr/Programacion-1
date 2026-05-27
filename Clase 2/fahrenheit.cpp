#include <iostream>
using std::cout;
using std::cin;
using std::endl;
int main(){
	int c, f;
	cout << "Ingrese la temperatura en celsius: ";
	cin >> c;
	f=(c*9/5)+32;
	cout << "El grado en fahrenheit es: " <<f;
	
	
	return 0;
}
