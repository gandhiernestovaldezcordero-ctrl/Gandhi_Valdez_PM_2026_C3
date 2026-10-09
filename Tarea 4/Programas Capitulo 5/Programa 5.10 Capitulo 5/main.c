#include <stdio.h>

/* Búsqueda secuencial en arreglos ordenados en forma creciente. */

const int MAX = 100;

/* Prototipos de funciones */
void Lectura(int A[], int T);
int Busca(int A[], int T, int E);

int main(void)
{
    int RES, ELE, TAM, VEC[MAX];

    /* Se verifica que el tamaño del arreglo sea correcto (entre 1 y 100) */
    do
    {
        printf("Ingrese el tamano del arreglo: ");
        scanf("%d", &TAM);
    }
    while (TAM > MAX || TAM < 1);

    Lectura(VEC, TAM);

    printf("\nIngrese el elemento a buscar: ");
    scanf("%d", &ELE);

    /* Se llama a la función que busca en el arreglo */
    RES = Busca(VEC, TAM, ELE);

    if (RES)
    {
        /* Si RES es diferente de 0, se escribe la posición en la que se encontró */
        printf("\nEl elemento se encuentra en la posicion: %d\n", RES);
    }
    else
    {
        printf("\nEl elemento no se encuentra en el arreglo\n");
    }

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

int Busca(int A[], int T, int E)
/* Esta función localiza en un arreglo ordenado en forma creciente un
elemento determinado. Si el elemento es encontrado, regresa su posición.
En caso contrario, regresa 0. */
{
    int I = 0, BAN = 0, RES;

    /* En arreglos ordenados crecientemente, si E es menor que A[I],
       se detiene la búsqueda ya que los siguientes elementos serán aún mayores. */
    while ((I < T) && (E >= A[I]) && !BAN)
    {
        if (A[I] == E)
        {
            BAN++;
        }
        else
        {
            I++;
        }
    }

    if (BAN)
    {
        RES = I + 1; /* Se asigna I + 1 dado que las posiciones en el arreglo comienzan en 0 */
    }
    else
    {
        RES = BAN;
    }

    return RES;
}
