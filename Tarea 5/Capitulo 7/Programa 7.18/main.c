#include <stdio.h>

/* Cadena invertida resuelta en forma recursiva. */

void inverso(char *cadena); /* Prototipo de función */

int main(void)
{
    char fra[50];

    printf("\nIngrese la linea de texto: ");
    gets(fra);

    printf("\nEscribe la linea de texto en forma inversa: ");
    inverso(fra);
    printf("\n");

    return 0;
}

void inverso(char *cadena)
/* La función inverso obtiene precisamente el inverso de la cadena. La solución
presentada es simple, pero para comprenderla es necesario tener conocimientos
tanto de pilas como de recursividad. Observa que mientras no se encuentre el
carácter de terminación de la cadena, se llama a la función recursiva con
el apuntador al siguiente carácter de la cadena. Por otra parte, queda
pendiente de ejecutar —almacenado en una pila— el carácter al cual apunta
*cadena. */
{
    if (cadena[0] != '\0')
    {
        inverso(&cadena[1]);
        putchar(cadena[0]);
    }
}
