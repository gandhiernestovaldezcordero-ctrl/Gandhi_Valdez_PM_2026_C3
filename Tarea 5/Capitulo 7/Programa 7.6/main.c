
#include <stdio.h>
#include <string.h>

/* Funciones de string.h para manejar cadenas */

int main(void)
{
    char cad0[100] = "Hola Mexico";
    char cad1[100], cad2[100];
    char cad3[20] = ", buenos dias!!!";
    char *c;

    /* Copiar cadenas */
    strcpy(cad1, cad0);
    printf("\nstrcpy: %s\n", cad1);

    strcpy(cad1, cad3);
    printf("strcpy: %s\n", cad1);

    strcpy(cad1, "XX");
    printf("strcpy: %s\n", cad1);

    /* Copiar una cantidad especifica de caracteres */
    strncpy(cad2, cad0, 4);
    cad2[4] = '\0';
    printf("strncpy: %s\n", cad2);

    strncpy(cad2, cad3, 3);
    cad2[3] = '\0';
    printf("strncpy: %s\n", cad2);

    /* Concatenar cadenas */
    strcat(cad0, cad3);
    printf("strcat: %s\n", cad0);

    strcat(cad1, " YY");
    printf("strcat: %s\n", cad1);

    strcpy(cad2, "Hola ");
    strncat(cad2, cad0, 4);
    printf("strncat: %s\n", cad2);

    /* Buscar una cadena dentro de otra */
    c = strstr(cad0, "Mexico");

    if (c != NULL)
        printf("Mexico se encontro: %s\n", c);
    else
        printf("Mexico no se encontro.\n");

    c = strstr(cad0, "Guatemala");

    if (c != NULL)
        printf("Guatemala se encontro: %s\n", c);
    else
        printf("Guatemala no se encontro.\n");

    return 0;
}
