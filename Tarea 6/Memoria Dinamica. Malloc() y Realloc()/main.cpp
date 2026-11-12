
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
    FILE *archivo;
    char nombreArchivo[100];
    char *contenido;
    int capacidad = 10;
    int cantidad = 0;
    int caracter;

    cout << "Ingrese el nombre del archivo: ";
    cin >> nombreArchivo;

    // Abrir el archivo en modo lectura
    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        cout << "Error: no se pudo abrir el archivo." << endl;
        return 1;
    }

    // Reservar memoria dinamica inicial
    contenido = (char*) malloc(capacidad * sizeof(char));

    if (contenido == NULL)
    {
        cout << "Error al reservar memoria." << endl;
        fclose(archivo);
        return 1;
    }

    // Leer el archivo caracter por caracter
    while ((caracter = fgetc(archivo)) != EOF)
    {
        // Aumentar la memoria si esta llena
        if (cantidad >= capacidad - 1)
        {
            capacidad *= 2;

            char *temporal = (char*) realloc(
                contenido, capacidad * sizeof(char));

            if (temporal == NULL)
            {
                cout << "Error al ampliar la memoria." << endl;
                free(contenido);
                fclose(archivo);
                return 1;
            }

            contenido = temporal;
        }

        contenido[cantidad] = (char) caracter;
        cantidad++;
    }

    // Colocar el caracter final de cadena
    contenido[cantidad] = '\0';

    fclose(archivo);

    // Mostrar el contenido del archivo
    cout << "\nContenido del archivo:\n" << endl;
    cout << contenido << endl;

    cout << "\nCaracteres leidos: " << cantidad << endl;
    cout << "Memoria reservada: " << capacidad << " bytes" << endl;

    // Liberar memoria dinamica
    free(contenido);

    return 0;
}
