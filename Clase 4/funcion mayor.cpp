#include <iostream>
using namespace std; 
int mayor(int a, int b){
	return (a<b) ? a:b;
}
int main(){
	int num1=10, num2=20;
	cout << "El mayor es: " << mayor(num1, num2) <<endl;
	return 0; 
}
