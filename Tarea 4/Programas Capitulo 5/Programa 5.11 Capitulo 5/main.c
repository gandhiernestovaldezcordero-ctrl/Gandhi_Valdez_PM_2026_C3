#include <stdio.h>

/* Búsqueda binaria. */

const int MAX = 100;

/* Prototipos de funciones */
void Lectura(int A[], int T);
int Binaria(int A[], int T, int E);

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

    /* Se llama a la función de búsqueda binaria */
    RES = Binaria(VEC, TAM, ELE);

    if (RES)
    {
        /* Si RES es diferente de 0, indica la posición (1-based) donde se encontró */
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

int Binaria(int A[], int T, int E)
/* Esta función busca el elemento E en el arreglo A de T elementos ordenados.
Si lo encuentra, regresa la posición en la que se ubica (1 a T); en caso
contrario, regresa 0. */
{
    int IZQ = 0, DER = T - 1, CEN, BAN = 0;

    while ((IZQ <= DER) && !BAN)
    {
        CEN = (IZQ + DER) / 2;

        if (E == A[CEN])
        {
            BAN = CEN + 1; /* Se guarda la posición (base 1) */
        }
        else if (E > A[CEN])
        {
            IZQ = CEN + 1;
        }
        else
        {
            DER = CEN - 1;
        }
    }

    return BAN;
}
