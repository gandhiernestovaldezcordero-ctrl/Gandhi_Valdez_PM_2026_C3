#include <stdio.h>
#include <string.h>

/* Bienes raíces.
El programa maneja información sobre las propiedades que tiene una empresa
de bienes raíces de la ciudad de Lima, Perú, tanto para venta como para
renta. */

typedef struct /* Declaración de la estructura ubicación. */
{
    char zona[20];
    char calle[20];
    char colo[20];        /* Colonia. */
} ubicacion;

typedef struct /* Declaración de la estructura propiedades. */
{
    char clave[5];
    float scu;            /* Superficie cubierta. */
    float ste;            /* Superficie terreno. */
    char car[50];         /* Características. */
    ubicacion ubi;        /* Observa que este campo es de tipo estructura ubicación. */
    float precio;
    char dispo;           /* Disponibilidad ('V' para Venta, 'R' para Renta). */
} propiedades;

void Lectura(propiedades A[], int T);
void F1(propiedades A[], int T); /* Prototipos de funciones. */
void F2(propiedades A[], int T);

int main(void)
{
    propiedades PROPIE[100];
    /* Se declara un arreglo unidimensional de tipo estructura propiedades. */
    int TAM;

    do
    {
        printf("Ingrese el número de propiedades (1-100): ");
        scanf("%d", &TAM);
    }
    while (TAM > 100 || TAM < 1);
    /* Se verifica que el tamaño del arreglo sea correcto. */

    Lectura(PROPIE, TAM);
    F1(PROPIE, TAM);
    F2(PROPIE, TAM);

    return 0;
}

void Lectura(propiedades A[], int T)
/* Esta función se utiliza para leer un arreglo unidimensional de tipo estructura
   propiedades de T elementos. */
{
    int I;
    for (I = 0; I < T; I++)
    {
        printf("\n--- Ingrese información de la propiedad %d ---", I + 1);

        while (getchar() != '\n'); /* Limpiar el búfer de entrada */

        printf("\nClave: ");
        gets(A[I].clave);

        printf("Superficie cubierta: ");
        scanf("%f", &A[I].scu);

        printf("Superficie terreno: ");
        scanf("%f", &A[I].ste);

        while (getchar() != '\n'); /* Limpiar el búfer antes de leer características */

        printf("Características: ");
        gets(A[I].car);

        printf("Zona: ");
        gets(A[I].ubi.zona);

        printf("Calle: ");
        gets(A[I].ubi.calle);

        printf("Colonia: ");
        gets(A[I].ubi.colo);

        printf("Precio: ");
        scanf("%f", &A[I].precio);

        while (getchar() != '\n'); /* Limpiar el búfer antes de leer disponibilidad */

        printf("Disponibilidad (V - Venta / R - Renta): ");
        scanf("%c", &A[I].dispo);
    }
}

void F1(propiedades A[], int T)
/* Esta función despliega las propiedades disponibles para venta cuya
   superficie cubierta sea mayor a 50 metros cuadrados y su precio esté
   entre 450,000 y 650,000. */
{
    int I;
    printf("\n\n\t\tListado de Propiedades para Venta (Superficie > 50, Precio 450k-650k)");

    for (I = 0; I < T; I++)
    {
        if ((A[I].dispo == 'V' || A[I].dispo == 'v') &&
            (A[I].scu > 50.0) &&
            (A[I].precio >= 450000.0) && (A[I].precio <= 650000.0))
        {
            printf("\n----------------------------------------");
            printf("\nClave de la propiedad: ");
            puts(A[I].clave);
            printf("Superficie cubierta: %.2f", A[I].scu);
            printf("\nSuperficie terreno: %.2f", A[I].ste);
            printf("\nCaracterísticas: ");
            puts(A[I].car);
            printf("Zona: ");
            puts(A[I].ubi.zona);
            printf("Calle: ");
            puts(A[I].ubi.calle);
            printf("Colonia: ");
            puts(A[I].ubi.colo);
            printf("Precio: %.2f\n", A[I].precio);
        }
    }
}

void F2(propiedades A[], int T)
/* Al recibir como datos una zona geográfica de Lima, Perú, y un cierto rango
   respecto al monto, esta función genera un listado de todas las propiedades
   disponibles para renta. */
{
    int I;
    float li, ls;
    char zon[20];

    printf("\n\n\t\tListado de Propiedades para Renta por Zona y Rango de Precio");

    while (getchar() != '\n'); /* Limpiar búfer remanente */

    printf("\nIngrese zona geográfica: ");
    gets(zon);

    printf("Ingrese el límite inferior del precio: ");
    scanf("%f", &li);

    printf("Ingrese el límite superior del precio: ");
    scanf("%f", &ls);

    for (I = 0; I < T; I++)
    {
        if ((A[I].dispo == 'R' || A[I].dispo == 'r') &&
            (strcmp(A[I].ubi.zona, zon) == 0) &&
            (A[I].precio >= li) && (A[I].precio <= ls))
        {
            printf("\n----------------------------------------");
            printf("\nClave de la propiedad: ");
            puts(A[I].clave);
            printf("Superficie cubierta: %.2f", A[I].scu);
            printf("\nSuperficie terreno: %.2f", A[I].ste);
            printf("\nCaracterísticas: ");
            puts(A[I].car);
            printf("Calle: ");
            puts(A[I].ubi.calle);
            printf("Colonia: ");
            puts(A[I].ubi.colo);
            printf("Precio: %.2f\n", A[I].precio);
        }
    }
}
