
#include <stdio.h>

#define PRODUCTOS 15
#define MESES 12

/* Prototipos de funciones */
void Lectura1(int [PRODUCTOS][MESES]);
void Lectura2(float [], int);
void Funcion1(int [][MESES], int, int, float [], float []);
void Funcion2(float [], int);
void Funcion3(float [], int);

int main(void)
{
    int FAB[PRODUCTOS][MESES] = {0};
    float COS[PRODUCTOS], VEN[PRODUCTOS];

    Lectura1(FAB);
    Lectura2(COS, PRODUCTOS);
    Funcion1(FAB, PRODUCTOS, MESES, COS, VEN);
    Funcion2(VEN, PRODUCTOS);
    Funcion3(VEN, PRODUCTOS);

    return 0;
}

void Lectura1(int A[][MESES])
{
    int MES, PRO, CAN;

    printf("\nIngrese mes, tipo de producto y cantidad vendida (-1 para terminar): ");
    scanf("%d %d %d", &MES, &PRO, &CAN);

    while (MES != -1 && PRO != -1 && CAN != -1)
    {
        if (MES >= 1 && MES <= MESES &&
            PRO >= 1 && PRO <= PRODUCTOS && CAN >= 0)
        {
            A[PRO - 1][MES - 1] += CAN;
        }
        else
        {
            printf("Datos invalidos. Intente nuevamente.\n");
        }

        printf("Ingrese mes, tipo de producto y cantidad vendida (-1 para terminar): ");
        scanf("%d %d %d", &MES, &PRO, &CAN);
    }
}

void Lectura2(float A[], int N)
{
    int I;

    for (I = 0; I < N; I++)
    {
        printf("Ingrese el precio del producto %d: ", I + 1);
        scanf("%f", &A[I]);
    }
}

void Funcion1(int A[][MESES], int F, int C,
              float V1[], float V2[])
{
    int I, J, SUM;

    printf("\n");

    for (I = 0; I < F; I++)
    {
        SUM = 0;

        for (J = 0; J < C; J++)
        {
            SUM += A[I][J];
        }

        V2[I] = V1[I] * SUM;

        printf("\nTotal de ventas del producto %d: %.2f",
               I + 1, V2[I]);
    }
}

void Funcion2(float A[], int C)
{
    int I;
    float SUM = 0.0;

    for (I = 0; I < C; I++)
    {
        SUM += A[I];
    }

    printf("\n\nTotal de ventas de la fabrica: %.2f\n", SUM);
}

void Funcion3(float A[], int C)
{
    int I, TPR = 0;
    float VEN = A[0];

    for (I = 1; I < C; I++)
    {
        if (VEN < A[I])
        {
            TPR = I;
            VEN = A[I];
        }
    }

    printf("\nProducto con mayores ventas: %d"
           "\nMonto de ventas: %.2f\n", TPR + 1, VEN);
}
