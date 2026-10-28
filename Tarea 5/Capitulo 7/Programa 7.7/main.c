
#include <stdio.h>
#include <string.h>

/* Otras funciones de string.h para manejar cadenas */

int main(void)
{
    int i;
    size_t longitud;
    char cad0[20] = "Hola Mexico";
    char cad1[20] = "Hola Guatemala";
    char cad2[20] = "Hola Venezuela";
    char cad3[20] = "Hola Mexico";
    char *c;
    char c3;

    /* Comparar cadenas */
    i = strcmp(cad0, cad1);
    printf("\nComparacion cad0 y cad1: %d", i);

    i = strcmp(cad0, cad2);
    printf("\nComparacion cad0 y cad2: %d", i);

    i = strcmp(cad0, cad3);
    printf("\nComparacion cad0 y cad3: %d", i);

    /* Obtener la longitud de las cadenas */
    longitud = strlen(cad0);
    printf("\nLongitud de cad0: %zu", longitud);

    longitud = strlen(cad1);
    printf("\nLongitud de cad1: %zu", longitud);

    /* Buscar el caracter G */
    c = strchr(cad1, 'G');

    if (c != NULL)
    {
        c3 = *c;
        printf("\nEl valor de c3 es: %c", c3);
    }
    else
    {
        printf("\nNo se encontro el caracter G.");
    }

    /* Buscar el caracter V */
    c = strchr(cad2, 'V');

    if (c != NULL)
    {
        c3 = *c;
        printf("\nEl valor de c3 es: %c", c3);
    }
    else
    {
        printf("\nNo se encontro el caracter V.");
    }

    printf("\n");

    return 0;
}
