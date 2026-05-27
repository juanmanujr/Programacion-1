#include<iostream>
using namespace std;
int main(){
	int numero;
	String respuesta;
	system("cls");
	cout<<"Ingrese un numero: ";
	cin>>numero;
	if(numero > 0){
		if(numero % 2 == 0){
			cout<<"El numero es par positivo"<<endl;
		}else{
			cout<<"El numero es impar positivo"<<endl;
		}
	}else{
		cout<<"El numero tiene que ser positivo"<<endl;
	}else{
		cout<<"Desea salir del programa ?: S N"<<endl;
		cin>>letra;
		if(letra == S){
			System.exit(0);
		}
	}
	system("pause");
	return 0;
}
