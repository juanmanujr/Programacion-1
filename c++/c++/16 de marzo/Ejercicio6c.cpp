#include<iostream>
using namespace std;
int main(){
	int dia;
	string nombre;
	cout<<"Ingrese un numero (1-7): ";
	cin>>dia;
	switch(dia){
		case 1:
			nombre = "Domingo";
			break;
		case 2:
			nombre = "Lunes";
			break;
		case 3:
			nombre = "Martes";
			break;
		case 4:
			nombre = "Miercoles";
			break;
		case 5:
			nombre = "Jueves";
			break;
		case 6:
			nombre = "Viernes";
			break;
		case 7:
			nombre = "Sabado";
			break;
		default:
			nombre = "El dato no corresponde";
			break;
	}
	cout<<nombre<<endl;
	system("pause");
	return 0;
}
