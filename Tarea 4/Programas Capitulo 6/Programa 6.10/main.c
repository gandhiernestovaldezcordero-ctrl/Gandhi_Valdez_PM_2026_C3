
#include <stdio.h>

#define MAX 50

/* Prototipos de funciones */
void Cuadrado(int [][MAX], int);
void Imprime(int [][MAX], int);

int main(void)
{
    int CMA[MAX][MAX], TAM;

    do
    {
        printf("Ingrese el tamano impar de la matriz: ");
        scanf("%d", &TAM);
    }
    while (TAM > MAX || TAM < 1 || TAM % 2 == 0);

    /* Se verifica el tamano y que sea impar */
    Cuadrado(CMA, TAM);
    Imprime(CMA, TAM);

    return 0;
}

/* Esta funcion se utiliza para formar el cuadrado magico */
void Cuadrado(int A[][MAX], int N)
{
    int I = 1, FIL = 0, COL = N / 2, NUM = N * N;

    while (I <= NUM)
    {
        A[FIL][COL] = I;

        if (I % N != 0)
        {
            FIL = (FIL - 1 + N) % N;
            COL = (COL + 1) % N;
        }
        else
        {
            FIL++;
        }

        I++;
    }
}

/* Esta funcion se utiliza para imprimir el cuadrado magico */
void Imprime(int A[][MAX], int N)
{
    int I, J;

    for (I = 0; I < N; I++)
    {
        for (J = 0; J < N; J++)
        {
            printf("%4d", A[I][J]);
        }
        printf("\n");
    }
}
