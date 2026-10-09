
#include <stdio.h>

#define MAX 50

/* Prototipos de funciones */
void Lectura(float [][MAX], int, int);
void Intercambia(float [][MAX], int, int);
void Imprime(float [][MAX], int, int);

int main(void)
{
    int F, C;
    float MAT[MAX][MAX];

    do
    {
        printf("Ingrese el numero de filas: ");
        scanf("%d", &F);
    }
    while (F > MAX || F < 1);

    do
    {
        printf("Ingrese el numero de columnas: ");
        scanf("%d", &C);
    }
    while (C > MAX || C < 1);

    Lectura(MAT, F, C);
    Intercambia(MAT, F, C);
    Imprime(MAT, F, C);

    return 0;
}

void Lectura(float A[][MAX], int F, int C)
{
    int I, J;

    for (I = 0; I < F; I++)
    {
        for (J = 0; J < C; J++)
        {
            printf("Ingrese el elemento %d %d: ", I + 1, J + 1);
            scanf("%f", &A[I][J]);
        }
    }
}

void Intercambia(float A[][MAX], int F, int C)
{
    int I, J;
    float AUX;

    for (I = 0; I < C / 2; I++)
    {
        for (J = 0; J < F; J++)
        {
            AUX = A[J][I];
            A[J][I] = A[J][C - I - 1];
            A[J][C - I - 1] = AUX;
        }
    }
}

void Imprime(float A[][MAX], int F, int C)
{
    int I, J;

    printf("\nMatriz despues del intercambio:\n");

    for (I = 0; I < F; I++)
    {
        for (J = 0; J < C; J++)
        {
            printf("%8.2f", A[I][J]);
        }
        printf("\n");
    }
}
