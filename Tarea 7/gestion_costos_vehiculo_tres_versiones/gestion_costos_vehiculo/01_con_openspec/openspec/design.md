# Diseño técnico

- Lenguaje: C estándar (C11).
- Persistencia: archivos de texto separados por punto y coma.
- `Expense`: estructura que representa un gasto.
- `gastos.csv`: almacena los gastos.
- `vehiculo.txt`: almacena los datos del vehículo.
- Validación: lectura de entradas mediante `fgets`, conversión con `strtol`/`strtod`.
- Resumen: normalización a costo mensual para permitir comparación.
- Gestión de errores: validar `fopen`, `malloc` no se utiliza en esta versión y cerrar archivos abiertos.
