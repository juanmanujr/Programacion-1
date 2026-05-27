//Define una función saludar que imprima "Hola mundo!" en la consola. 

#include <iostream>
using namespace std;
void duplicar( int &num){
	num*= 2;
}


int main(){
	int x=5;
	duplicar (x);
	cout << "Valor despues de llamar a duplicar: " << x << endl;
	
	
	
	return 0; 
}
