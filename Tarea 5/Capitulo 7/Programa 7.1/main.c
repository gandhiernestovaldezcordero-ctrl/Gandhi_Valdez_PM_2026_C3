
#include <stdio.h>

/* Funciones para el manejo de caracteres de la biblioteca stdio.h */

int main(void)
{
    char p1, p2, p3 = '$';

    /* Leer un caracter y mostrarlo */
    printf("\nIngrese un caracter: ");
    p1 = getchar();
    putchar(p1);

    /* Mostrar el caracter almacenado en p3 */
    printf("\n\nEl caracter p3 es: ");
    putchar(p3);

    /* Leer otro caracter */
    printf("\n\nIngrese otro caracter: ");
    scanf(" %c", &p2);

    /* Mostrar el segundo caracter */
    printf("El caracter ingresado es: %c\n", p2);

    return 0;
}
