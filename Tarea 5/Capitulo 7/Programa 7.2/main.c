
#include <stdio.h>
#include <ctype.h>

/* Funciones para el manejo de caracteres de la biblioteca ctype.h */

int main(void)
{
    char p1;

    printf("\nIngrese un caracter para analizar si es un digito: ");
    p1 = getchar();

    if (isdigit((unsigned char)p1))
        printf("%c es un digito\n", p1);
    else
        printf("%c no es un digito\n", p1);

    /* Leer el siguiente caracter ignorando saltos de linea */
    printf("\nIngrese un caracter para examinar si es una letra: ");
    scanf(" %c", &p1);

    if (isalpha((unsigned char)p1))
        printf("%c es una letra\n", p1);
    else
        printf("%c no es una letra\n", p1);

    printf("\nIngrese un caracter para examinar si es una letra minuscula: ");
    scanf(" %c", &p1);

    if (isalpha((unsigned char)p1))
    {
        if (islower((unsigned char)p1))
            printf("%c es una letra minuscula\n", p1);
        else
            printf("%c no es una letra minuscula\n", p1);
    }
    else
    {
        printf("%c no es una letra\n", p1);
    }

    printf("\nIngrese una letra para convertirla de mayuscula a minuscula: ");
    scanf(" %c", &p1);

    if (isalpha((unsigned char)p1))
    {
        if (isupper((unsigned char)p1))
            printf("%c fue convertida de mayuscula a minuscula\n",
                   tolower((unsigned char)p1));
        else
            printf("%c es una letra minuscula\n", p1);
    }
    else
    {
        printf("%c no es una letra\n", p1);
    }

    return 0;
}
