
#include <stdio.h>
#include <string.h>

/* Funciones para el manejo de cadenas de caracteres */

int main(void)
{
    char *cad0 = "Buenos dias";
    char cad1[20] = "Hola";
    char cad2[] = "Mexico";
    char cad3[] = {'B', 'i', 'e', 'n', 'v', 'e', 'n', 'i', 'd', 'o', '\0'};
    char cad4[100], cad5[20], cad6[100];
    char p;
    int i = 0;
    int ch;

    printf("\nLa cadena cad0 es: ");
    puts(cad0);

    printf("\nLa cadena cad1 es: ");
    printf("%s\n", cad1);

    printf("\nLa cadena cad2 es: ");
    puts(cad2);

    printf("\nLa cadena cad3 es: ");
    puts(cad3);

    printf("\nIngrese una linea de texto (se lee con fgets):\n");
    getchar(); /* Consume el salto de linea pendiente, si lo hay */
    fgets(cad4, sizeof(cad4), stdin);
    cad4[strcspn(cad4, "\n")] = '\0';

    printf("\nLa cadena cad4 es: ");
    puts(cad4);

    printf("\nIngrese una sola palabra (se lee con scanf):\n");
    scanf("%19s", cad5);

    printf("\nLa cadena cad5 es: ");
    printf("%s\n", cad5);

    /* Consumir lo que queda de la linea anterior */
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* No hace nada; limpia la entrada */
    }

    printf("\nIngrese una linea de texto (se lee con getchar):\n");

    while (i < (int)sizeof(cad6) - 1 &&
           (ch = getchar()) != '\n' && ch != EOF)
    {
        p = (char)ch;
        cad6[i++] = p;
    }

    cad6[i] = '\0';

    printf("\nLa cadena cad6 es: ");
    puts(cad6);

    return 0;
}
