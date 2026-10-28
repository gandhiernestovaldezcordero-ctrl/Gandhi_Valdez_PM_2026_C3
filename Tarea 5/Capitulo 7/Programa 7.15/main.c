#include <stdio.h>
#include <ctype.h>

/* Decodifica.
El programa decodifica una cadena de caracteres compuesta por números y
letras. */

void interpreta(char *cadena); /* Prototipo de función */

int main(void)
{
    char cad[50];

    printf("\nIngrese la cadena de caracteres: ");
    gets(cad);

    interpreta(cad);

    return 0;
}

void interpreta(char *cadena)
/* Esta función se utiliza para decodificar la cadena de caracteres. */
{
    int i = 0, j, k;

    while (cadena[i] != '\0')
    {
        if (isalpha(cadena[i]))   /* Se utiliza isalpha para observar si el carácter es una letra. */
        {
            k = cadena[i - 1] - 48;
            /* En la variable entera k se almacena el ASCII del número —convertido
            en carácter— que nos interesa, menos 48 que corresponde al ASCII
            del dígito 0. */
            for (j = 0; j < k; j++)
            {
                putchar(cadena[i]);
            }
        }
        i++;
    }
    printf("\n");
}
