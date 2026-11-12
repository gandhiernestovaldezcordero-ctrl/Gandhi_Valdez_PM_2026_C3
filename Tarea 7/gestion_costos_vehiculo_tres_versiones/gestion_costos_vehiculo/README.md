# Sistema de Gestión de Costos de Vehículos

Este paquete contiene tres entregables en lenguaje C:

1. `01_con_openspec/`: versión de consola y documentación de desarrollo guiado por especificaciones (OpenSpec).
2. `02_sin_openspec/`: la misma solución funcional desarrollada directamente, sin OpenSpec.
3. `03_interfaz_gtk/`: versión de escritorio con interfaz gráfica GTK 3.

## Funcionalidades
- Registrar datos básicos del vehículo.
- Registrar gastos: seguro, marbete, revista, préstamo, depreciación, impuestos/permisos, parqueo mensual, combustible, mantenimiento, neumáticos, aceite, reparaciones, estacionamiento por horas y lavado.
- Consultar los gastos registrados.
- Calcular costos mensuales y anuales estimados.
- Guardar datos en archivos locales (`vehiculo.txt` y `gastos.csv`).

## Formato de los gastos
`fecha;categoria;descripcion;monto;kilometraje;frecuencia`

La frecuencia es `1` mensual, `2` anual y `3` pago único. Para comparar los costos, los gastos anuales y los pagos únicos se prorratean entre 12 meses. Es una estimación presupuestaria, no un cálculo contable ni una valoración de mercado.

## Compilar las versiones de consola
Desde la carpeta de cada versión:
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o gestion_costos
./gestion_costos
```
En Windows con MinGW:
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o gestion_costos.exe
gestion_costos.exe
```

## Compilar GTK 3
Requiere GTK 3 instalado y `pkg-config` disponible:
```bash
gcc -std=c11 -Wall -Wextra `pkg-config --cflags gtk+-3.0` main.c -o gestion_costos_gtk `pkg-config --libs gtk+-3.0`
./gestion_costos_gtk
```
En Windows se recomienda instalar GTK 3 mediante MSYS2 (entorno UCRT64) y compilar desde la terminal UCRT64 con `pkg-config`.

## Archivos de datos
El programa crea los archivos en el directorio de trabajo desde el que se ejecuta. Haz una copia de seguridad de `gastos.csv` y `vehiculo.txt` antes de mover o eliminar datos.

## Limitaciones de esta primera entrega
- Los campos de fecha se guardan como texto; se recomienda escribir `AAAA-MM-DD`.
- La descripción no debe contener punto y coma (`;`) porque ese carácter separa las columnas del archivo.
- La versión GTK ofrece registro, consulta y resumen; la versión de consola también incluye consulta del vehículo.
- Los pagos únicos se distribuyen entre 12 meses para ofrecer un promedio orientativo.
