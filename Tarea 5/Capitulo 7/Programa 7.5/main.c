#include <stdio.h>
#include <stdlib.h>

/* Funciones para convertir cadenas numericas */

int main(void)
{
    int i;
    double d;
    long l;
    char cad0[100];
    char *cad1;

    printf("\nIngrese una cadena numerica entera: ");
    if (fgets(cad0, sizeof(cad0), stdin) == NULL)
        return 1;

    i = atoi(cad0);
    printf("Cadena: %sValor convertido + 3: %d\n", cad0, i + 3);

    printf("\nIngrese una cadena numerica decimal: ");
    if (fgets(cad0, sizeof(cad0), stdin) == NULL)
        return 1;

    d = atof(cad0);
    printf("Valor convertido + 1.50: %.2f\n", d + 1.50);

    d = strtod(cad0, &cad1);
    printf("Resultado de strtod: %.2f\n", d);

    l = atol(cad0);
    printf("Resultado de atol: %ld\n", l);

    return 0;
}
