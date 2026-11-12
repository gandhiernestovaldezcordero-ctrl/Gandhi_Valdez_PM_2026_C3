#include <stdio.h>

/* Alumnos.
   El programa pregunta al usuario el número de registro que desea
   modificar, obtiene el nuevo promedio del alumno y modifica tanto el
   registro como el archivo correspondiente. */

typedef struct {
    int matricula;
    char nombre[20];
    int carrera;
    float promedio;
} alumno;
/* Declaración de la estructura alumno. */

void modifica(FILE *);    /* Prototipo de función. */

void main(void)
{
    FILE *ar;

    if ((ar = fopen("ad1.dat", "r+")) != NULL)
    {
        modifica(ar);
        fclose(ar);
    }
    else
    {
        printf("\nEl archivo no se puede abrir");
    }
}

void modifica(FILE *ap)
/* Esta función se utiliza para modificar el promedio de un alumno. */
{
    int d;
    alumno alu;

    printf("\nIngrese el número de registro que desea modificar: ");
    /* Observa que el lenguaje C almacena el primer registro en la
       posición cero. Por lo tanto, si desea modificar el registro n,
       debe buscarlo en la posición n-1. */
    scanf("%d", &d);

    fseek(ap, (d - 1) * sizeof(alumno), 0);
    /* Observa que la instrucción fseek tiene tres argumentos. El primero
       indica que el apuntador se debe posicionar al inicio del FILE.
       El segundo señala el número de bloques que debe moverse, en términos
       de bytes, para llegar al registro correspondiente... */

    fread(&alu, sizeof(alumno), 1, ap);
    /* Luego de posicionarnos en el registro que nos interesa, lo leemos. */

    printf("\nIngrese el promedio correcto del alumno: ");
    scanf("%f", &alu.promedio);
    /* Modificamos el registro con el nuevo promedio. */

    fseek(ap, (d - 1) * sizeof(alumno), 0);
    /* Nos tenemos que posicionar nuevamente en el lugar correcto para
       escribir el registro modificado. */

    fwrite(&alu, sizeof(alumno), 1, ap);
}
