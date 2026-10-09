
#include <stdio.h>

/* Casa de bolsa.
   El programa recibe los precios mensuales de las acciones de cinco
   fondos de inversion y el precio al 31 de diciembre de 2003.
   Genera informacion estadistica sobre los fondos.
*/

void LecturaM(float [][12], int, int);
void LecturaV(float [], int);
void F1(float [][12], int, int, float [], float []);
void F2(float [][12], int, int);
void F3(float [], int);

int main(void)
{
    float FON[5][12], PRE[5], REN[5];

    LecturaM(FON, 5, 12);
    LecturaV(PRE, 5);
    F1(FON, 5, 12, PRE, REN);
    F2(FON, 5, 12);
    F3(REN, 5);

    return 0;
}

/* Lee los precios mensuales de los fondos */
void LecturaM(float A[][12], int F, int C)
{
    int I, J;

    for (I = 0; I < F; I++)
    {
        for (J = 0; J < C; J++)
        {
            printf("Precio fondo %d, mes %d: ", I + 1, J + 1);
            scanf("%f", &A[I][J]);
        }
    }
}

/* Lee los precios al 31/12/2003 */
void LecturaV(float A[], int T)
{
    int I;

    printf("\n");

    for (I = 0; I < T; I++)
    {
        printf("Precio fondo %d al 31/12/2003: ", I + 1);
        scanf("%f", &A[I]);
    }
}

/* Calcula el rendimiento anual de cada fondo */
void F1(float A[][12], int F, int C, float B[], float V[])
{
    int I;

    printf("\nRENDIMIENTOS ANUALES DE LOS FONDOS\n");

    for (I = 0; I < F; I++)
    {
        if (B[I] != 0)
        {
            V[I] = ((A[I][C - 1] - B[I]) / B[I]) * 100;
            printf("Fondo %d: %.2f%%\n", I + 1, V[I]);
        }
        else
        {
            V[I] = 0;
            printf("Fondo %d: no se puede calcular (precio inicial cero)\n",
                   I + 1);
        }
    }
}

/* Calcula el promedio anual de los precios mensuales */
void F2(float A[][12], int F, int C)
{
    int I, J;
    float SUM, PRO;

    printf("\nPROMEDIO ANUAL DE LAS ACCIONES DE LOS FONDOS\n");

    for (I = 0; I < F; I++)
    {
        SUM = 0;

        for (J = 0; J < C; J++)
        {
            SUM += A[I][J];
        }

        PRO = SUM / C;

        printf("Fondo %d: %.2f\n", I + 1, PRO);
    }
}

/* Determina los fondos con mejor y peor rendimiento */
void F3(float A[], int F)
{
    float ME = A[0], PE = A[0];
    int M = 0, P = 0, I;

    for (I = 1; I < F; I++)
    {
        if (A[I] > ME)
        {
            ME = A[I];
            M = I;
        }

        if (A[I] < PE)
        {
            PE = A[I];
            P = I;
        }
    }

    printf("\nMEJOR Y PEOR FONDO DE INVERSION\n");
    printf("Mejor fondo: %d\tRendimiento: %.2f%%\n", M + 1, ME);
    printf("Peor fondo: %d\tRendimiento: %.2f%%\n", P + 1, PE);
}
