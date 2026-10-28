
#include <stdio.h>

/* Declaracion de cadenas de caracteres y asignacion de valores */

int main(void)
{
    char *cad0;
    char cad1[100];
    char cad2[20];

    cad0 = "Argentina";
    puts(cad0);

    cad0 = "Brasil";
    puts(cad0);

    printf("\nIngrese una cadena para cad1: ");
    if (fgets(cad1, sizeof(cad1), stdin) != NULL)
    {
        puts(cad1);
    }

    /* Declaracion y lectura correcta de cad2 */
    snprintf(cad2, sizeof(cad2), "Mexico");
    puts(cad2);

    printf("\nIngrese una nueva cadena para cad2: ");
    if (fgets(cad2, sizeof(cad2), stdin) != NULL)
    {
        puts(cad2);
    }

    return 0;
}
