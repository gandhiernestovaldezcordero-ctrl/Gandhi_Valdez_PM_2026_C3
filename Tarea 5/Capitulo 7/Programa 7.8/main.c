
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Minusculas y mayusculas.
   Determina el numero de letras minusculas y mayusculas
   que hay en cada cadena de caracteres. */

void minymay(char *cadena);

/* Prototipo de funcion. */

int main(void)
{
    int i, n;
    char FRA[20][50];

    printf("\nIngrese el numero de filas del arreglo (1-20): ");
    scanf("%d", &n);

    if (n < 1 || n > 20)
    {
        printf("Error: el numero debe estar entre 1 y 20.\n");
        return 1;
    }

    /* Limpiar el salto de linea que deja scanf. */
    getchar();

    for (i = 0; i < n; i++)
    {
        printf("Ingrese la linea %d de texto: ", i + 1);

        if (fgets(FRA[i], sizeof(FRA[i]), stdin) != NULL)
        {
            /* Eliminar el salto de linea si existe. */
            FRA[i][strcspn(FRA[i], "\n")] = '\0';
        }
    }

    for (i = 0; i < n; i++)
    {
        printf("\nCadena %d: %s\n", i + 1, FRA[i]);
        minymay(FRA[i]);
    }

    return 0;
}

void minymay(char *cadena)
{
    int i = 0, mi = 0, ma = 0;

    while (cadena[i] != '\0')
    {
        if (islower((unsigned char)cadena[i]))
            mi++;
        else if (isupper((unsigned char)cadena[i]))
            ma++;

        i++;
    }

    printf("Numero de letras minusculas: %d\n", mi);
    printf("Numero de letras mayusculas: %d\n", ma);
}
