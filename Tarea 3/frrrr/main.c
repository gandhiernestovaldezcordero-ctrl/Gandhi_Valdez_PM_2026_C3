#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#define SALIR 0
#define SUMAR 1
#define DIVIDIR 2
#define RAIZ 3
#define CUADRADO 4
#define ERR_OK 0
#define ERR_DIV_BY_ZERO 789
#define ERR_NEGATIVE 790

int suma(double num1, double num2, double *result);
int dividir(double dividendo, double denominador, double *result);
int raizCuadrada(double numero, double *result);
int elevarAlCuadrado(double numero, double *result);

int main(void)
{
    int menu = -1;
    int err = ERR_OK;
    double n1 = 0.0;
    double n2 = 0.0;
    double r = 0.0;

    do {
        printf("\n\n0-SALIR\n1-SUMAR\n2-DIVIDIR\n");
        printf("3-RAIZ CUADRADA\n4-ELEVAR AL CUADRADO\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &menu);

        if (menu == SUMAR) {
            printf("Ingresa el primer sumando: ");
            scanf("%lf", &n1);
            printf("Ingresa el segundo sumando: ");
            scanf("%lf", &n2);

            err = suma(n1, n2, &r);
            if (err == ERR_OK)
                printf("Suma de %lf mas %lf es %lf\n", n1, n2, r);
        }
        else if (menu == DIVIDIR) {
            printf("Ingresa el dividendo: ");
            scanf("%lf", &n1);
            printf("Ingresa el denominador: ");
            scanf("%lf", &n2);

            err = dividir(n1, n2, &r);
            if (err == ERR_OK)
                printf("Division de %lf entre %lf es %lf\n", n1, n2, r);
            else
                printf("Error: no se puede dividir entre cero.\n");
        }
        else if (menu == RAIZ) {
            printf("Ingresa el numero: ");
            scanf("%lf", &n1);

            err = raizCuadrada(n1, &r);
            if (err == ERR_OK)
                printf("La raiz cuadrada de %lf es %lf\n", n1, r);
            else
                printf("Error: no se puede calcular la raiz de un numero negativo.\n");
        }
        else if (menu == CUADRADO) {
            printf("Ingresa el numero: ");
            scanf("%lf", &n1);

            err = elevarAlCuadrado(n1, &r);
            if (err == ERR_OK)
                printf("%lf elevado al cuadrado es %lf\n", n1, r);
        }
        else if (menu != SALIR) {
            printf("Opcion no valida.\n");
        }

    } while (menu != SALIR);

    return 0;
}

int suma(double num1, double num2, double *result)
{
    *result = num1 + num2;
    return ERR_OK;
}

int dividir(double dividendo, double denominador, double *result)
{
    if (denominador == 0.0)
        return ERR_DIV_BY_ZERO;

    *result = dividendo / denominador;
    return ERR_OK;
}

int raizCuadrada(double numero, double *result)
{
    if (numero < 0.0)
        return ERR_NEGATIVE;

    if (numero == 0.0) {
        *result = 0.0;
        return ERR_OK;
    }

    /* Método de Newton: aproxima x tal que x*x = numero. */
    double aproximacion = numero >= 1.0 ? numero : 1.0;
    double anterior;

    do {
        anterior = aproximacion;
        aproximacion = 0.5 * (anterior + numero / anterior);
    } while ((aproximacion - anterior) > 1e-10);

    *result = aproximacion;
    return ERR_OK;
}

int elevarAlCuadrado(double numero, double *result)
{
    *result = numero * numero;
    return ERR_OK;
}
