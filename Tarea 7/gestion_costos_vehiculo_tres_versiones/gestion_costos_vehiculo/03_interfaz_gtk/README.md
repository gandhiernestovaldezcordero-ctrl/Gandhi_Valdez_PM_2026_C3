# Versión gráfica GTK 3

Interfaz de escritorio escrita en C con GTK 3. Incluye pestañas para registrar el vehículo, registrar gastos, consultar los gastos y calcular el resumen.

Compilación en Linux:
```bash
gcc -std=c11 -Wall -Wextra `pkg-config --cflags gtk+-3.0` main.c -o gestion_costos_gtk `pkg-config --libs gtk+-3.0`
./gestion_costos_gtk
```

En Windows, instala GTK 3 y pkg-config mediante MSYS2 (terminal UCRT64). La aplicación guarda los datos en `vehiculo.txt` y `gastos.csv` en el directorio de ejecución.
