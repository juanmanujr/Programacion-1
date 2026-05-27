#include <iostream>
#include <string>
using namespace std;
//definicion de la clase
class Perro{
	public: // acceso publico visible fuera de la clase 
		string nombre; //atributo
		int edad; //atributo
		//metodo {funciona dentro de la clase}
		void ladrar(){
			cout << nombre << "dice :  ¡Guau! ¡Guau!";
		}
};

int main(){
	//creacion de un objeto {intancia de Perro}
	Perro miPerro;
	miPerro.nombre = "Firulais ";  
	miPerro.edad = 3; 
	// usar un metodo del objeto
	miPerro.ladrar(); //salida: "Firulairs dice: !Guau! Guau
	
	return 0;
	
}
