#include <stdio.h>

/* Alumnos.
   El programa lee bloques —variables de tipo estructura alumno— de un archivo
   de acceso directo. */

typedef struct {
    int matricula;
    char nombre[20];
    int carrera;
    float promedio;
} alumno;
/* Declaración de la estructura alumno. */

void lee(FILE *);    /* Prototipo de función. */

void main(void)
{
    FILE *ar;

    if ((ar = fopen("ad1.dat", "r")) != NULL)
    {
        lee(ar);
        fclose(ar);
    }
    else
    {
        printf("\nEl archivo no se puede abrir");
    }
}

void lee(FILE *ap)
/* Esta función se utiliza para leer bloques de un archivo de acceso directo. */
{
    alumno alu;

    fread(&alu, sizeof(alumno), 1, ap);
    /* Observa que la función fread tiene los mismos argumentos que la función
       fwrite del programa anterior. También es importante tomar nota de que cuando
       tenemos que leer los registros de un archivo utilizando una estructura
       repetitiva como el while, debemos realizar una primera lectura antes de
       ingresar al ciclo y luego las siguientes dentro del ciclo, pero como última
       instrucción del mismo... */

    while (!feof(ap))
    {
        printf("\nMatrícula: %d", alu.matricula);
        printf("\tCarrera: %d", alu.carrera);
        printf("\tPromedio: %.2f\t ", alu.promedio);
        puts(alu.nombre);

        fread(&alu, sizeof(alumno), 1, ap);
    }
}
