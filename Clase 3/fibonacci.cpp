#include <iostream>
using std::cout;
using std::cin;
using std::endl;
int main() {
    int n, a = 0, b = 1, siguiente;
    cout << "Ingrese la cantidad de terminos: ";
    cin >> n;
    cout << "Serie de Fibonacci: ";
    for (int i = 0; i < n; i++) {
        cout << a << " ";
        siguiente = a + b;
        a = b;
        b = siguiente;
    }
    cout << endl;
    return 0;
}

