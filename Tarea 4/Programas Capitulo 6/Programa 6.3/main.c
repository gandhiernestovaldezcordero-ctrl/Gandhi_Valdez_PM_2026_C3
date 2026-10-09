
#include <stdio.h>

/* Universidad */

#define F 8
#define C 2
#define P 5

/* Prototipos de funciones */
void Lectura(int [][C][P], int, int, int);
void Funcion1(int [][C][P], int, int, int);
void Funcion2(int [][C][P], int, int, int);
void Funcion3(int [][C][P], int, int, int);

int main(void)
{
    int UNI[F][C][P];

    Lectura(UNI, F, C, P);
    Funcion1(UNI, F, C, P);
    Funcion2(UNI, F, C, P);
    Funcion3(UNI, 6, C, P);

    return 0;
}

void Lectura(int A[][C][P], int FI, int CO, int PR)
{
    int K, I, J;

    for (K = 0; K < PR; K++)
    {
        for (I = 0; I < FI; I++)
        {
            for (J = 0; J < CO; J++)
            {
                printf("Anio: %d\tCarrera: %d\tSemestre: %d: ",
                       K + 1, I + 1, J + 1);
                scanf("%d", &A[I][J][K]);
            }
        }
    }
}

void Funcion1(int A[][C][P], int FI, int CO, int PR)
{
    int K, I, J, MAY = 0, AO = -1, SUM;

    /* Determinar el año con mayor ingreso */

    for (K = 0; K < PR; K++)
    {
        SUM = 0;

        for (I = 0; I < FI; I++)
        {
            for (J = 0; J < CO; J++)
            {
                SUM += A[I][J][K];
            }
        }

        if (SUM > MAY)
        {
            MAY = SUM;
            AO = K;
        }
    }

    printf("\nAnio con mayor ingreso: %d"
           "\nCantidad de alumnos: %d\n", AO + 1, MAY);
}

void Funcion2(int A[][C][P], int FI, int CO, int PR)
{
    int I, J, MAY = 0, CAR = -1, SUM;

    /* Determinar la carrera con mayor ingreso en el ultimo año */

    for (I = 0; I < FI; I++)
    {
        SUM = 0;

        for (J = 0; J < CO; J++)
        {
            SUM += A[I][J][PR - 1];
        }

        if (SUM > MAY)
        {
            MAY = SUM;
            CAR = I;
        }
    }

    printf("\nCarrera con mayor ingreso en el ultimo anio: %d"
           "\nCantidad de alumnos: %d\n", CAR + 1, MAY);
}

void Funcion3(int A[][C][P], int FI, int CO, int PR)
{
    int K, J, MAY = 0, AO = -1, SUM;

    /* Determinar el año con mayor ingreso en la carrera indicada */

    for (K = 0; K < PR; K++)
    {
        SUM = 0;

        for (J = 0; J < CO; J++)
        {
            SUM += A[FI - 1][J][K];
        }

        if (SUM > MAY)
        {
            MAY = SUM;
            AO = K;
        }
    }

    printf("\nAnio con mayor ingreso en la carrera %d: %d"
           "\nCantidad de alumnos: %d\n", FI, AO + 1, MAY);
}
