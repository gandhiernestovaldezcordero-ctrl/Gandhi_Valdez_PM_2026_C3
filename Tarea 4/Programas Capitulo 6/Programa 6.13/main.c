
#include <stdio.h>

#define MES 12
#define DEP 3
#define ANO 8

/* Prototipos de funciones */
void Lectura(float [MES][DEP][ANO], int, int, int);
void Funcion1(float [MES][DEP][ANO], int, int, int);
void Funcion2(float [MES][DEP][ANO], int, int, int);
void Funcion3(float [MES][DEP][ANO], int, int, int);

int main(void)
{
    float PRO[MES][DEP][ANO];

    Lectura(PRO, MES, DEP, ANO);
    Funcion1(PRO, MES, DEP, 2);
    Funcion2(PRO, MES, DEP, ANO);
    Funcion3(PRO, MES, DEP, ANO);

    return 0;
}

/* Lee las ventas mensuales de los departamentos */
void Lectura(float A[][DEP][ANO], int F, int C, int P)
{
    int K, I, J;

    for (K = 0; K < P; K++)
    {
        for (I = 0; I < F; I++)
        {
            for (J = 0; J < C; J++)
            {
                printf("Ano: %d\tMes: %d\tDepartamento: %d: ",
                       K + 1, I + 1, J + 1);
                scanf("%f", &A[I][J][K]);
            }
        }
    }
}

/* Ventas totales de la empresa en el segundo ano */
void Funcion1(float A[][DEP][ANO], int F, int C, int P)
{
    int I, J;
    float SUM = 0.0;

    for (I = 0; I < F; I++)
    {
        for (J = 0; J < C; J++)
        {
            SUM += A[I][J][P - 1];
        }
    }

    printf("\n\nVentas totales de la empresa en el segundo ano: %.2f\n",
           SUM);
}

/* Departamento con mayores ventas en el ultimo ano */
void Funcion2(float A[][DEP][ANO], int F, int C, int P)
{
    int I, J, MAYOR = 0;
    float SUM[DEP] = {0.0, 0.0, 0.0};

    for (I = 0; I < F; I++)
    {
        for (J = 0; J < C; J++)
        {
            SUM[J] += A[I][J][P - 1];
        }
    }

    for (J = 1; J < C; J++)
    {
        if (SUM[J] > SUM[MAYOR])
        {
            MAYOR = J;
        }
    }

    printf("\nDepartamento con mayores ventas en el ultimo ano: ");

    switch (MAYOR)
    {
        case 0:
            printf("Hilos");
            break;
        case 1:
            printf("Lanas");
            break;
        case 2:
            printf("Licra");
            break;
    }

    printf("\nVentas: %.2f\n", SUM[MAYOR]);
}

/* Departamento, mes y ano con la mayor venta */
void Funcion3(float A[][DEP][ANO], int F, int C, int P)
{
    int K, I, J;
    int DE = 0, ME = 0, AN = 0;
    float VEN = A[0][0][0];

    for (K = 0; K < P; K++)
    {
        for (I = 0; I < F; I++)
        {
            for (J = 0; J < C; J++)
            {
                if (A[I][J][K] > VEN)
                {
                    VEN = A[I][J][K];
                    DE = J;
                    ME = I;
                    AN = K;
                }
            }
        }
    }

    printf("\n\nDepartamento: ");

    switch (DE)
    {
        case 0:
            printf("Hilos");
            break;
        case 1:
            printf("Lanas");
            break;
        case 2:
            printf("Licra");
            break;
    }

    printf("\nMes: %d\tAno: %d", ME + 1, AN + 1);
    printf("\nVentas: %.2f\n", VEN);
}
