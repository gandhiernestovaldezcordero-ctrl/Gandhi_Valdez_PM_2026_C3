# Versión sin OpenSpec

Esta versión se desarrolló directamente a partir de los requisitos del proyecto, sin utilizar el flujo de especificaciones OpenSpec. Su funcionamiento es equivalente al de la primera versión: perfil del vehículo, registro y consulta de gastos, y resumen mensual/anual.

Compilación:
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o gestion_costos
./gestion_costos
```

Los archivos `gastos.csv` y `vehiculo.txt` se crean en el directorio desde el que se ejecuta el programa.
