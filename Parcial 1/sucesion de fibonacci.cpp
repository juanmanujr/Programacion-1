//Realizar la progresion de Fibonnaci (Puede que salga en el examen)
#include <iostream>
using namespace std;

int main(){
	int a=0, b=1, c, n, siguiente, i;
	cout << "Cuantos terminos de la progesion Fibonnaci queres ver: ";
	cin >> n;
	for (i=0; i<n; i++){
		cout << a <<" " ;
		siguiente= a+b;//calcula el numero siguiente como la suma de los dos anteriores
		//actualiza los nuevos valores para la siguiente tabla
		a=b;
		b=siguiente;
	}
	return 0;
}
