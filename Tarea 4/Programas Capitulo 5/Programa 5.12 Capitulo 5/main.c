#include <stdio.h>

/* Ordenación por inserción directa. */

const int MAX = 100;

/* Prototipos de funciones */
void Lectura(int A[], int T);
void Ordena(int A[], int T);
void Imprime(int A[], int T);

int main(void)
{
    int TAM, VEC[MAX];

    /* Se verifica que el tamaño del arreglo sea correcto (entre 1 y 100) */
    do
    {
        printf("Ingrese el tamano del arreglo: ");
        scanf("%d", &TAM);
    }
    while (TAM > MAX || TAM < 1);

    Lectura(VEC, TAM);
    Ordena(VEC, TAM);
    Imprime(VEC, TAM);

    return 0;
}

void Lectura(int A[], int T)
/* La función Lectura se utiliza para leer un arreglo unidimensional de T
elementos de tipo entero. */
{
    int I;
    for (I = 0; I < T; I++)
    {
        printf("Ingrese el elemento %d: ", I + 1);
        scanf("%d", &A[I]);
    }
}

void Imprime(int A[], int T)
/* La función Imprime se utiliza para escribir un arreglo unidimensional de T
elementos de tipo entero. */
{
    int I;
    for (I = 0; I < T; I++)
    {
        printf("\nA[%d]: %d", I, A[I]);
    }
    printf("\n");
}

void Ordena(int A[], int T)
/* Esta función ordena los elementos del arreglo unidimensional A mediante
el método de inserción directa. */
{
    int I, L, AUX;

    for (I = 1; I < T; I++)
    {
        AUX = A[I];
        L = I - 1;

        while ((L >= 0) && (AUX < A[L]))
        {
            A[L + 1] = A[L];
            L--;
        }

        A[L + 1] = AUX;
    }
}
