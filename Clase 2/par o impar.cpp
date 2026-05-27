#include <iostream>
using std:: cout;
using std:: cin;
using std:: endl;
int main(){
	int n;
	cout << "Ingrese un numero: ";
	cin >> n;
	if (n%2==0){
		cout << "\nEs par";
	}else{
		cout << "\nEs impar";
	}
	
	return 0;
}
