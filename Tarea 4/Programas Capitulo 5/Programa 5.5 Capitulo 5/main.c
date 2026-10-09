#include <stdio.h>

const int TAM = 50;

/* Prototipos de funciones */
void Lectura(int VEC[], int T);
void Frecuencia(int A[], int P, int B[], int T);
void Impresion(int VEC[], int T);
void Mayor(int *X, int T);

int main(void)
{
    int CAL[TAM], FRE[6] = {0};

    /* Lectura de las calificaciones de los alumnos */
    Lectura(CAL, TAM);

    /* Cálculo de frecuencias para calificaciones de 0 a 5 */
    Frecuencia(CAL, TAM, FRE, 6);

    printf("\nFrecuencia de Calificaciones\n");
    Impresion(FRE, 6);
    Mayor(FRE, 6);

    return 0;
}

void Lectura(int VEC[], int T)
{
    int I;
    printf("\n");
    for (I = 0; I < T; I++)
    {
        printf("Ingrese la calificacion (0-5) del alumno %d: ", I + 1);
        scanf("%d", &VEC[I]);
    }
}

void Frecuencia(int A[], int P, int B[], int T)
{
    int I;
    for (I = 0; I < P; I++)
    {
        if ((A[I] >= 0) && (A[I] < T))
        {
            B[A[I]]++;
        }
    }
}

void Impresion(int VEC[], int T)
{
    int I;
    for (I = 0; I < T; I++)
    {
        printf("\nCalificacion %d: %d alumnos", I, VEC[I]);
    }
}

void Mayor(int *X, int T)
{
    int I, MFRE = 0, MVAL = X[0];

    for (I = 1; I < T; I++)
    {
        if (MVAL < X[I])
        {
            MFRE = I;
            MVAL = X[I];
        }
    }
    printf("\n\nMayor frecuencia de calificaciones -> Calificacion: %d \tCantidad: %d\n", MFRE, MVAL);
}
