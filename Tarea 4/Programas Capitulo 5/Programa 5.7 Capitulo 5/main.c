#include <stdio.h>

/* Arreglo sin elementos repetidos.
El programa, al recibir como dato un arreglo unidimensional desordenado de N
elementos, obtiene como salida ese mismo arreglo pero sin los elementos
repetidos. */

/* Prototipos de funciones */
void Lectura(int A[], int T);
void Imprime(int A[], int T);
void Elimina(int A[], int *T);

int main(void)
{
    int TAM, ARRE[100];

    /* Se escribe un do-while para verificar que el tamaño del arreglo que se
       ingresa sea valido. */
    do
    {
        printf("Ingrese el tamano del arreglo (1 - 100): ");
        scanf("%d", &TAM);
    }
    while (TAM > 100 || TAM < 1);

    Lectura(ARRE, TAM);

    /* El tamaño del arreglo se pasa por referencia ya que disminuira */
    Elimina(ARRE, &TAM);

    Imprime(ARRE, TAM);

    return 0;
}

void Lectura(int A[], int T)
/* La función Lectura se utiliza para leer un arreglo unidimensional de T
elementos de tipo entero. */
{
    int I;
    printf("\n");
    for (I = 0; I < T; I++)
    {
        printf("Ingrese el elemento %d: ", I + 1);
        scanf("%d", &A[I]);
    }
}

void Imprime(int A[], int T)
/* La función Imprime se utiliza para escribir un arreglo unidimensional, sin
repeticiones, de T elementos de tipo entero. */
{
    int I;
    for (I = 0; I < T; I++)
    {
        printf("\nA[%d]: %d", I, A[I]);
    }
    printf("\n");
}

void Elimina(int A[], int *T)
/* Esta función se utiliza para eliminar los elementos repetidos de un arreglo
unidimensional de T elementos de tipo entero. */
{
    int I = 0, K, L;
    while (I < (*T - 1))
    {
        K = I + 1;
        while (K <= (*T - 1))
        {
            if (A[I] == A[K])
            {
                for (L = K; L < (*T - 1); L++)
                {
                    A[L] = A[L + 1];
                }
                *T = *T - 1;
            }
            else
            {
                K++;
            }
        }
        I++;
    }
}
