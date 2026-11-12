# Especificación funcional

## Capacidad: perfil del vehículo
- El sistema permite guardar marca, modelo, año y placa en `vehiculo.txt`.
- El sistema permite consultar el contenido guardado.

## Capacidad: registro de gastos
- El sistema presenta las 14 categorías requeridas.
- Cada gasto contiene fecha, categoría, descripción, monto positivo, kilometraje y frecuencia.
- La frecuencia puede ser mensual, anual o pago único.
- Los gastos se anexan a `gastos.csv`.

## Capacidad: consulta
- El sistema lista los registros válidos con sus datos principales.
- Si el archivo no existe, informa que todavía no hay registros.

## Capacidad: resumen
- Mensual: gasto mensual tal cual; gasto anual dividido entre 12; pago único dividido entre 12 como estimación.
- Anual: costo mensual estimado multiplicado por 12.
- Se muestra el total por categoría.

## Escenarios
### Registro correcto
Dado que el usuario introduce datos válidos, cuando confirma el registro, entonces el gasto queda añadido al archivo.

### Archivo inexistente
Dado que no hay archivo de gastos, cuando el usuario solicita consultar o calcular, entonces el sistema informa que no hay datos.

### Monto inválido
Dado que el monto debe ser positivo, cuando el usuario introduce cero o un valor negativo, entonces se solicita nuevamente.
