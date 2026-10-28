#include <stdio.h>
#include <string.h>

/* Vendedores.
El programa maneja información sobre las ventas que realizan los vendedores de
artículos domésticos de una importante empresa de la Ciudad de México. */

typedef struct /* Declaración de la estructura banco. */
{
    char noba[10];       /* Nombre del banco. */
    char nucu[10];       /* Número de cuenta. */
} banco;

typedef union /* Declaración de la unión fpago. */
{
    banco che;           /* Cheque. Campo de tipo estructura banco. */
    banco nomi;          /* Nómina. Campo de tipo estructura banco. */
    char venta;          /* Ventanilla. */
} fpago;

typedef struct /* Declaración de la estructura domicilio. */
{
    char cnu[20];        /* Calle y número. */
    char col[20];        /* Colonia. */
    char cp[5];          /* Código Postal. */
    char ciu[15];        /* Ciudad. */
} domicilio;

typedef struct /* Declaración de la estructura vendedor. */
{
    int num;             /* Número de vendedor. */
    char nom[20];        /* Nombre del vendedor. */
    float ven[12];       /* Ventas del año. Arreglo unidimensional de tipo real. */
    domicilio domi;      /* domi es de tipo estructura domicilio. */
    float sal;           /* Salario mensual. */
    fpago pago;          /* pago es de tipo unión fpago. */
    int cla;             /* Clave forma de pago. */
} vendedor;

void Lectura(vendedor A[], int T);
void F1(vendedor A[], int T);
void F2(vendedor A[], int T);
void F3(vendedor A[], int T);        /* Prototipos de funciones. */
void F4(vendedor A[], int T);

int main(void)
{
    vendedor VENDEDORES[100];
    /* Declaración del arreglo unidimensional de tipo estructura vendedor. */
    int TAM;

    do
    {
        printf("Ingrese el número de vendedores (1-100): ");
        scanf("%d", &TAM);
    }
    while (TAM > 100 || TAM < 1);
    /* Se verifica que el número de elementos del arreglo sea correcto. */

    Lectura(VENDEDORES, TAM);
    F1(VENDEDORES, TAM);
    F2(VENDEDORES, TAM);
    F3(VENDEDORES, TAM);
    F4(VENDEDORES, TAM);

    printf("\n\tFIN DEL PROGRAMA\n");

    return 0;
}

void Lectura(vendedor A[], int T)
/* Esta función se utiliza para leer un arreglo unidimensional de tipo
   estructura vendedor de T elementos. */
{
    int I, J;
    for (I = 0; I < T; I++)
    {
        printf("\n\tIngrese datos del vendedor %d", I + 1);
        printf("\nNúmero de vendedor: ");
        scanf("%d", &A[I].num);

        while (getchar() != '\n'); /* Limpiar el búfer de entrada */

        printf("Nombre del vendedor: ");
        gets(A[I].nom);

        printf("Ventas del año:\n");
        for (J = 0; J < 12; J++)
        {
            printf("\tMes %d: ", J + 1);
            scanf("%f", &A[I].ven[J]);
        }

        while (getchar() != '\n'); /* Limpiar el búfer después del último scanf */

        printf("Domicilio del vendedor:\n");
        printf("\tCalle y número: ");
        gets(A[I].domi.cnu);

        printf("\tColonia: ");
        gets(A[I].domi.col);

        printf("\tCódigo Postal: ");
        gets(A[I].domi.cp);

        printf("\tCiudad: ");
        gets(A[I].domi.ciu);

        printf("Salario del vendedor: ");
        scanf("%f", &A[I].sal);

        printf("Forma de Pago (Banco - 1, Nómina - 2, Ventanilla - 3): ");
        scanf("%d", &A[I].cla);

        switch (A[I].cla)
        {
            case 1:
            {
                while (getchar() != '\n'); /* Limpiar búfer */
                printf("\tNombre del banco: ");
                gets(A[I].pago.che.noba);
                printf("\tNúmero de cuenta: ");
                gets(A[I].pago.che.nucu);
                break;
            }
            case 2:
            {
                while (getchar() != '\n'); /* Limpiar búfer */
                printf("\tNombre del banco: ");
                gets(A[I].pago.nomi.noba);
                printf("\tNúmero de cuenta: ");
                gets(A[I].pago.nomi.nucu);
                break;
            }
            case 3:
            {
                A[I].pago.venta = 'S';
                break;
            }
        }
    }
}

void F1(vendedor A[], int T)
/* Esta función se utiliza para generar las ventas totales anuales de cada uno
   de los vendedores de la empresa. */
{
    int I, J;
    float SUM;

    printf("\n\n\t\tVentas Totales de los Vendedores");
    for (I = 0; I < T; I++)
    {
        printf("\nVendedor: %d", A[I].num);
        SUM = 0.0;
        for (J = 0; J < 12; J++)
        {
            SUM += A[I].ven[J];
        }
        printf("\nVentas: %.2f\n", SUM);
    }
}

void F2(vendedor A[], int T)
/* Esta función se utiliza para incrementar 5% el salario de todos aquellos
   vendedores cuyas ventas anuales superaron $1,500,000. */
{
    int I, J;
    float SUM;

    printf("\n\n\t\tIncremento a los Vendedores con Ventas > 1,500,000$");
    for (I = 0; I < T; I++)
    {
        SUM = 0.0;
        for (J = 0; J < 12; J++)
        {
            SUM += A[I].ven[J];
        }
        if (SUM > 1500000.00)
        {
            A[I].sal = A[I].sal * 1.05;
            printf("\nNúmero de empleado: %d\nVentas: %.2f\nNuevo salario: %.2f\n",
                   A[I].num, SUM, A[I].sal);
        }
    }
}

void F3(vendedor A[], int T)
/* Esta función se utiliza para generar un listado de todos aquellos
   vendedores que en el año vendieron menos de $300,000. */
{
    int I, J;
    float SUM;

    printf("\n\n\t\tVendedores con Ventas < 300,000");
    for (I = 0; I < T; I++)
    {
        SUM = 0.0;
        for (J = 0; J < 12; J++)
        {
            SUM += A[I].ven[J];
        }
        if (SUM < 300000.00)
        {
            printf("\nNúmero de empleado: %d\nNombre: %s\nVentas: %.2f\n",
                   A[I].num, A[I].nom, SUM);
        }
    }
}

void F4(vendedor A[], int T)
/* Esta función se usa para imprimir el número de empleado, el nombre del
   banco y el número de cuenta de todos aquellos empleados a quienes se les
   deposita su sueldo en cuenta de cheques. */
{
    int I;

    printf("\n\n\t\tVendedores con Cuenta en el Banco");
    for (I = 0; I < T; I++)
    {
        if (A[I].cla == 1)
        {
            printf("\nNúmero de vendedor: %d\nBanco: %s\nCuenta: %s\n",
                   A[I].num, A[I].pago.che.noba, A[I].pago.che.nucu);
        }
    }
}
