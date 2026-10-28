#include <stdio.h>

/* Calcula longitud.
El programa calcula la longitud de la cadena sin utilizar la función strlen. */

int cuenta(char *cadena); /* Prototipo de función */

int main(void)
{
    int i;
    char cad[50];

    printf("\nIngrese la cadena de caracteres: ");
    gets(cad);

    i = cuenta(cad);

    printf("\nLongitud de la cadena: %d\n", i);

    return 0;
}

int cuenta(char *cadena)
/* La función calcula la longitud de la cadena. */
{
    int c = 0;
    while (cadena[c] != '\0')
    {
        c++;
    }
    return c;
}
