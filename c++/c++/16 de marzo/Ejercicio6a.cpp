#include<iostream>
using namespace std;
int main(){
	int dia;
	string nombre;
	cout<<"Ingrese un numero (1-7): ";
	cin>>dia;
	if(dia == 1){
		nombre = "Domingo";
	}else{
		if(dia == 2){
			nombre = "Lunes";
		}else{
			if(dia == 3){
				nombre = "Martes";
			}else{
				if(dia == 4){
					nombre = "Miercoles";
				}else{
					if(dia == 5){
						nombre = "Jueves";
					}else{
						if(dia == 6){
							nombre = "Viernes";
						}else{
							if(dia == 7){
								nombre = "Sabado";
							}else{
								nombre = "El dato no corresponde";
							}
						}
					}
				}
			}
		}
	}
	cout<<nombre<<endl;
	system("pause");
	return 0;
}
