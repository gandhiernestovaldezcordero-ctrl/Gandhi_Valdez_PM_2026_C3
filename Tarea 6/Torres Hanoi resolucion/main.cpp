
#include <iostream>
using namespace std;

// Funcion recursiva para resolver las Torres de Hanoi
void Hanoi(int discos, char origen, char auxiliar, char destino)
{
    if (discos == 1)
    {
        cout << "Mover disco 1 desde " << origen
             << " hasta " << destino << endl;
    }
    else
    {
        Hanoi(discos - 1, origen, destino, auxiliar);

        cout << "Mover disco " << discos << " desde "
             << origen << " hasta " << destino << endl;

        Hanoi(discos - 1, auxiliar, origen, destino);
    }
}

int main()
{
    int discos;

    cout << "==================================" << endl;
    cout << "       TORRES DE HANOI" << endl;
    cout << "==================================" << endl;

    cout << "Ingrese la cantidad de discos: ";
    cin >> discos;

    if (discos <= 0)
    {
        cout << "Error: debe ingresar un numero positivo." << endl;
    }
    else
    {
        cout << "\nSolucion del problema:\n" << endl;

        Hanoi(discos, 'A', 'B', 'C');

        cout << "\nCantidad minima de movimientos: "
             << (1LL << discos) - 1 << endl;
    }

    return 0;
}

