#include <stdio.h>
/* Apuntadores, variables y valores. */
void main(void)
{int  X = 3, Y = 7, Z[5] = {2, 4, 6, 8, 10};
printf("\nX = %d \t Y = %d \t Z[0] = %d \t Z[1] = %d \t Z[3] = %d \t Z[4]= %d", X, Y,
Z[0], Z[1], Z[2], Z[3], Z[4]);
int *IX; /* IIXX representa un apuntador a un entero. */
IX = &X; /* IIXX apunta a XX. IIXX tiene la dirección de XX. */
Y = *IX; /* YYtoma el valor de XX, ahora vale 33. */
*IX = 1; /* XXse modifica, ahora vale 11. */
printf("\nX = %d \t Y = %d \t Z[0] = %d \t Z[1] = %d \t Z[2] = %d \t Z[3] = %d\t Z[4] =  %d", X, Y, Z[0], Z[1], Z[2], Z[3], Z[4]);
IX = &Z[2]; /* IIXX apunta al tercer elemento del arreglo ZZ. */
Y = *IX; /* YYtoma el valor de ZZ[[22], ahora vale 66. */
*IX = 15; /* ZZ[[22]] se modifica, ahora vale 1155. */
printf("\nX = %d \t Y = %d \t Z[0] = %d \t Z[1] = %d \t Z[2] = %d \t Z[3] = %d\t Z[4] = %d", X, Y, Z[0], Z[1], Z[2], Z[3], Z[4]);
X = *IX + 5;      /* XXse modifica, ahora vale ZZ[[22]]  ++  55  ==  2200. Recuerda que **IIXX
contiene el valor de ZZ[[22]].. */
*IX = *IX - 5; /* ZZ[[22]] se modifica, ahora vale 1100. */
printf("\nX = %d \t Y = %d \t Z[0] = %d \t Z[1] = %d \t Z[2] = %d \t Z[3] = %d\t Z[4] = %d", X, Y, Z[0], Z[1], Z[2], Z[3], Z[4]);
++*IX; /* ZZ[[22]]se modifica, se incrementa en 1. ZZ[[22]]ahora vale 1111. */
*IX += 1;          /* ZZ[[22]] se vuelve a modificar, ahora vale 1122. */
printf("\nX = %d \t Y = %d \t Z[0] = %d \t Z[1] = %d \t Z[2] = %d \t Z[3] = %d\t Z[4] = %d", X, Y, Z[0], Z[1], Z[2], Z[3], Z[4]);
X = *(IX + 1); /* XXse modifica. El apuntador IIXX accede temporalmente a
ZZ[[33]], por lo tanto XXtoma este valor ((88)). Observa que IIXX no se reasigna */
Y = *IX;            /* YYse modifica, toma el valor de ZZ[[22]]  ((1122)). */
printf("\nX = %d \t Y = %d \t Z[0] = %d \t Z[1] = %d \t Z[2] = %d \t Z[3] = %d\t Z[4] = %d", X, Y, Z[0], Z[1], Z[2], Z[3], Z[4]);
IX = IX + 1; /* IIXX se modifica. Observa la forma de mover el apuntador.
Ahora IIXX apunta al cuarto elemento de ZZ  ((ZZ[[33]])). */
Y = *IX;            /* YYse modifica, ahora vale ZZ[[33]]  ((88)). */
printf("\nX = %d \t Y = %d \t Z[0]= %d \t Z[1] = %d \t Z[2] = %d \t Z[3] = %d\t Z[4] = %d", X, Y, Z[0], Z[1], Z[2], Z[3], Z[4]);
IX = IX + 4; /* IIXX se modifica. Observa que el apuntador se mueve
4 posiciones y cae en una dirección afuera del arreglo. Esto ocasionará un
error. */ Y = *IX; /* YYse modifica, toma el valor (basura) de una celda
incorrecta. Es un error que no señala el compilador del lenguaje CC. */
printf("\nX = %d \t Y = %d \t Z[0]= %d \t Z[1] = %d \t Z[2] = %d \t Z[3] = %d\t Z[4] =      %d", X, Y, Z[0], Z[1], Z[2], Z[3], Z[4]);
IX = &X; /* IIXX  apunta a la variable entera XX. */
IX = IX + 1; /* IIXXse mueve una posición y cae en una celda incorrecta. */
X = *IX; /* XXtoma el valor (basura) de la celda a la que apunta IIXX.*/
printf("\nX = %d \t Y = %d \t Z[0]= %d \t Z[1] = %d \t Z[2] = %d \t Z[3] = %d\t Z[4] =    %d", X, Y, Z[0], Z[1], Z[2], Z[3], Z[4]);
}
