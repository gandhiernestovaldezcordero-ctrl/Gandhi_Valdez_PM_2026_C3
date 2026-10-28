#include <stdio.h>
#include <string.h>

/* Cadena invertida.
El programa obtiene la cadena invertida. */

char *inverso(char *cadena); /* Prototipo de función */

int main(void)
{
    char fra[50], aux[50];

    printf("\nIngrese la linea de texto: ");
    gets(fra);

    /* Se copia a aux el resultado de la función inverso. */
    strcpy(aux, inverso(fra));

    printf("\nEscribe la linea de texto en forma inversa: ");
    puts(aux);

    return 0;
}

char *inverso(char *cadena)
/* La función calcula el inverso de una cadena y regresa el resultado al
programa principal. */
{
    int i = 0, j, lon;
    char temp;

    lon = strlen(cadena);
    j = lon - 1;

    /* Observa que el reemplazo de los caracteres se debe realizar solamente
       hasta la mitad de la cadena. */
    while (i < (lon / 2))
    {
        temp = cadena[i];
        cadena[i] = cadena[j];
        cadena[j] = temp;
        i++;
        j--;
    }

    return cadena;
}
