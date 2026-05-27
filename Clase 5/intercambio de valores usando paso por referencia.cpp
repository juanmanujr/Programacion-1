//crear una funcion que intercambie los valores de dos variables usando paso por referencia

#include <iostream>
using namespace std;
void intercambio (int &a, int &b){
	int intercambio;
	a=b;
	intercambio=b;
	b=a;
	
}


int main(){
	int n1, n2;
	cout << "Ingrese un numero a:  ";
	cin >> n1;
	cout << "Ingrese un numero b: ";
	cin >> n2;
	intercambio(n1, n2);
	cout << "valor a= " << n1 << " valor b= " <<n2;
	
	
	return 0; 
}
