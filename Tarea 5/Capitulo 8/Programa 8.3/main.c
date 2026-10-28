#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructuras-3.
El programa muestra la manera en que se declara una estructura anidada, así
como la forma de acceso a los campos de las variables o apuntadores de tipo
estructura, tanto para lectura como para escritura. Se utiliza además una
funcion que recibe como parametro un apuntador de tipo estructura. */

typedef struct /* Declaración de la estructura domicilio utilizando un typedef. */
{
    char calle[20];
    int numero;
    int cp;
    char localidad[20];
} domicilio;

struct empleado /* Declaración de la estructura anidada empleado. */
{
    char nombre[20];
    char departamento[20];
    float sueldo;
    domicilio direccion; /* direccion es un campo de tipo estructura domicilio de la estructura empleado. */
};

void Lectura(struct empleado *a); /* Prototipo de función */

int main(void)
{
    struct empleado e0 = {"Arturo", "Compras", 15500.75, {"San Jeronimo", 120, 3490, "Toluca"}};
    struct empleado *e1, *e2, e3, e4;

    /* Se declaran diferentes variables y apuntadores de la estructura empleado
       para que el lector pueda apreciar también las diferentes formas en que los
       campos reciben valores. */

    /* En el programa principal se leen los campos de una variable, e3, y un
       apuntador de tipo estructura, *e1. */

    e1 = (struct empleado *)malloc(sizeof(struct empleado));
    if (e1 == NULL)
    {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    printf("\nIngrese el nombre del empleado 1: ");
    scanf("%s", e1->nombre);

    while (getchar() != '\n'); /* Limpiar el búfer de entrada */

    printf("Ingrese el departamento de la empresa: ");
    gets(e1->departamento);

    printf("Ingrese el sueldo del empleado: ");
    scanf("%f", &e1->sueldo);

    printf("----Ingrese la direccion del empleado----");
    printf("\n\tCalle: ");

    while (getchar() != '\n'); /* Limpiar el búfer de entrada */

    gets(e1->direccion.calle); /* Corregido el error de sintaxis del original (e1->dirección, calle) */

    printf("\tNumero: ");
    scanf("%d", &e1->direccion.numero);

    printf("\tCodigo Postal: ");
    scanf("%d", &e1->direccion.cp);

    printf("\tLocalidad: ");

    while (getchar() != '\n'); /* Limpiar el búfer de entrada */

    gets(e1->direccion.localidad);

    printf("\nIngrese el nombre del empleado 3: ");
    scanf("%s", e3.nombre);

    while (getchar() != '\n'); /* Limpiar el búfer de entrada */

    printf("Ingrese el departamento de la empresa: ");
    gets(e3.departamento);

    printf("Ingrese el sueldo del empleado: ");
    scanf("%f", &e3.sueldo);

    printf("----Ingrese la direccion del empleado----");
    printf("\n\tCalle: ");

    while (getchar() != '\n'); /* Limpiar el búfer de entrada */

    gets(e3.direccion.calle);

    printf("\tNumero: ");
    scanf("%d", &e3.direccion.numero);

    printf("\tCodigo Postal: ");
    scanf("%d", &e3.direccion.cp);

    printf("\tLocalidad: ");

    while (getchar() != '\n'); /* Limpiar el búfer de entrada */

    gets(e3.direccion.localidad);

    /* En la función Lectura se leen los campos de una variable, e4, y un apuntador
       de tipo estructura, *e2. */

    e2 = (struct empleado *)malloc(sizeof(struct empleado));
    if (e2 == NULL)
    {
        printf("Error al asignar memoria.\n");
        free(e1);
        return 1;
    }

    Lectura(e2);
    Lectura(&e4);

    printf("\nDatos del empleado 1\n");
    printf("%s\t%s\t%.2f\t%s\t%d\t%d\t%s\n",
           e1->nombre, e1->departamento, e1->sueldo,
           e1->direccion.calle, e1->direccion.numero,
           e1->direccion.cp, e1->direccion.localidad);

    printf("\nDatos del empleado 4\n");
    printf("%s\t%s\t%.2f\t%s\t%d\t%d\t%s\n",
           e4.nombre, e4.departamento, e4.sueldo,
           e4.direccion.calle, e4.direccion.numero,
           e4.direccion.cp, e4.direccion.localidad);

    /* Liberar la memoria dinámica asignada */
    free(e1);
    free(e2);

    return 0;
}

void Lectura(struct empleado *a)
/* Función que permite leer los campos de un apuntador de tipo estructura empleado. */
{
    printf("\nIngrese el nombre del empleado: ");
    gets(a->nombre);

    printf("Ingrese el departamento de la empresa: ");
    gets(a->departamento);

    printf("Ingrese el sueldo del empleado: ");
    scanf("%f", &a->sueldo);

    while (getchar() != '\n'); /* Limpiar el búfer de entrada */

    printf("----Ingrese la direccion del empleado----");
    printf("\n\tCalle: ");
    gets(a->direccion.calle);

    printf("\tNumero: ");
    scanf("%d", &a->direccion.numero);

    printf("\tCodigo Postal: ");
    scanf("%d", &a->direccion.cp);

    while (getchar() != '\n'); /* Limpiar el búfer de entrada */

    printf("\tLocalidad: ");
    gets(a->direccion.localidad);
}
