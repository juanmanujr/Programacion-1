#include <iostream>
using namespace std;

void ordenar(int &x, int &y) { 
    if (x > y) {
        int z = x;
        x = y;
        y = z;
    }
}

int main() {
    int a = 5, b = 3;

    cout << "Antes de ordenar: a = " << a << ", b = " << b << endl;

    ordenar(a, b); 

    cout << "Después de ordenar: a = " << a << ", b = " << b << endl;

    return 0;
}
