# Propuesta: sistema de gestión de costos de vehículos

## Problema
El propietario necesita registrar los gastos relacionados con su vehículo y conocer su costo mensual y anual estimado.

## Objetivo
Crear una aplicación de consola en C que permita registrar el vehículo, agregar gastos, consultar registros y generar un resumen de costos.

## Alcance
Incluye persistencia local mediante archivos de texto, 14 categorías de gastos y clasificación por frecuencia (mensual, anual o pago único).

## Fuera de alcance
Sin conexión a bancos, facturación electrónica, sincronización en la nube ni valoración automática del vehículo.

## Criterios de aceptación
- El usuario puede registrar y consultar los datos básicos del vehículo.
- El usuario puede registrar gastos con fecha, categoría, descripción, monto, kilometraje y frecuencia.
- Los registros permanecen guardados al cerrar el programa.
- El resumen muestra montos registrados y promedios mensual/anual.
- Los errores al abrir o escribir archivos se informan sin continuar usando un puntero inválido.
