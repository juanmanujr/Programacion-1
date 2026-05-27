#include<iostream>
using namespace std;
int main(){
	int dia;
	string nombre;
	cout<<"Ingrese un numero (1-7): ";
	cin>>dia;
	if(dia == 1){
		nombre = "Domingo";
	}
	if(dia == 2){
		nombre = "Lunes";
	}
	if(dia == 3){
		nombre = "Martes";
	}
	if(dia == 4){
		nombre = "Miercoles";
	}
	if(dia == 5){
		nombre = "Jueves";
	}
	if(dia == 6){
		nombre = "Viernes";
	}
	if(dia == 7){
		nombre = "Sabado";
	}
	if(dia < 1 || dia > 7){
		nombre = "El dato no corresponde";
	}
	cout<<nombre<<endl;
	system("pause");
	return 0;
}
