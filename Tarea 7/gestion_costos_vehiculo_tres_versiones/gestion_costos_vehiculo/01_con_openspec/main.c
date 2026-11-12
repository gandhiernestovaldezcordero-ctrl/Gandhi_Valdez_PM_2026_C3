#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "gastos.csv"
#define VEHICLE_FILE "vehiculo.txt"
#define MAX_LINE 512
#define MAX_TEXT 120

typedef struct {
    char date[11];
    int category;
    char description[MAX_TEXT];
    double amount;
    double odometer;
    int frequency; /* 1=mensual, 2=anual, 3=unico */
} Expense;

const char *categories[] = {
    "Seguro", "Marbete", "Revista vehicular", "Prestamo",
    "Depreciacion", "Impuestos y permisos", "Parqueo mensual",
    "Combustible", "Mantenimiento", "Neumaticos", "Aceite",
    "Reparaciones", "Estacionamiento por horas", "Lavado"
};
#define CATEGORY_COUNT 14

void read_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        buffer[0] = '\0';
    }
}

int read_int(const char *prompt, int min, int max) {
    char line[80];
    char *end;
    long value;
    for (;;) {
        printf("%s", prompt);
        read_line(line, sizeof line);
        value = strtol(line, &end, 10);
        if (end != line && *end == '\0' && value >= min && value <= max)
            return (int)value;
        printf("Entrada invalida. Intente de nuevo.\n");
    }
}

double read_double(const char *prompt, double min) {
    char line[80];
    char *end;
    double value;
    for (;;) {
        printf("%s", prompt);
        read_line(line, sizeof line);
        value = strtod(line, &end);
        if (end != line && *end == '\0' && value >= min)
            return value;
        printf("Monto/valor invalido. Intente de nuevo.\n");
    }
}

void load_vehicle(void) {
    FILE *f = fopen(VEHICLE_FILE, "r");
    char line[200];
    if (!f) {
        printf("\nNo hay datos del vehiculo registrados.\n");
        return;
    }
    printf("\n--- VEHICULO REGISTRADO ---\n");
    while (fgets(line, sizeof line, f)) printf("%s", line);
    fclose(f);
}

void register_vehicle(void) {
    char brand[80], model[80], year[20], plate[40];
    FILE *f;
    printf("Marca: "); read_line(brand, sizeof brand);
    printf("Modelo: "); read_line(model, sizeof model);
    printf("Ano: "); read_line(year, sizeof year);
    printf("Placa: "); read_line(plate, sizeof plate);
    f = fopen(VEHICLE_FILE, "w");
    if (!f) { perror("No se pudo guardar el vehiculo"); return; }
    fprintf(f, "Marca: %s\nModelo: %s\nAno: %s\nPlaca: %s\n",
            brand, model, year, plate);
    fclose(f);
    printf("Vehiculo guardado correctamente.\n");
}

void list_categories(void) {
    int i;
    for (i = 0; i < CATEGORY_COUNT; i++)
        printf("%2d. %s\n", i + 1, categories[i]);
}

void add_expense(void) {
    Expense e;
    FILE *f;
    printf("\nFecha (AAAA-MM-DD): ");
    read_line(e.date, sizeof e.date);
    printf("\nCategorias:\n"); list_categories();
    e.category = read_int("Seleccione categoria: ", 1, CATEGORY_COUNT) - 1;
    printf("Descripcion: "); read_line(e.description, sizeof e.description);
    e.amount = read_double("Monto en RD$: ", 0.01);
    e.odometer = read_double("Kilometraje (0 si no aplica): ", 0.0);
    printf("Frecuencia: 1=mensual, 2=anual, 3=pago unico\n");
    e.frequency = read_int("Seleccione frecuencia: ", 1, 3);

    f = fopen(DATA_FILE, "a");
    if (!f) { perror("No se pudo abrir el archivo de gastos"); return; }
    fprintf(f, "%s;%d;%s;%.2f;%.2f;%d\n", e.date, e.category,
            e.description, e.amount, e.odometer, e.frequency);
    fclose(f);
    printf("Gasto registrado correctamente.\n");
}

int parse_expense(char *line, Expense *e) {
    char *token;
    token = strtok(line, ";"); if (!token) return 0; snprintf(e->date, sizeof e->date, "%s", token);
    token = strtok(NULL, ";"); if (!token) return 0; e->category = atoi(token);
    token = strtok(NULL, ";"); if (!token) return 0; snprintf(e->description, sizeof e->description, "%s", token);
    token = strtok(NULL, ";"); if (!token) return 0; e->amount = atof(token);
    token = strtok(NULL, ";"); if (!token) return 0; e->odometer = atof(token);
    token = strtok(NULL, ";\r\n"); if (!token) return 0; e->frequency = atoi(token);
    return e->category >= 0 && e->category < CATEGORY_COUNT &&
           e->amount > 0 && e->frequency >= 1 && e->frequency <= 3;
}

double monthly_cost(const Expense *e) {
    if (e->frequency == 1) return e->amount;
    if (e->frequency == 2) return e->amount / 12.0;
    return e->amount / 12.0; /* estimacion: pago unico distribuido en 12 meses */
}

void list_expenses(void) {
    FILE *f = fopen(DATA_FILE, "r");
    char line[MAX_LINE];
    Expense e;
    int count = 0;
    if (!f) { printf("Todavia no hay gastos registrados.\n"); return; }
    printf("\n%-10s | %-24s | %-22s | %12s | %10s | %s\n",
           "Fecha", "Categoria", "Descripcion", "Monto RD$", "Km", "Frecuencia");
    printf("---------------------------------------------------------------------------------------------------------\n");
    while (fgets(line, sizeof line, f)) {
        if (parse_expense(line, &e)) {
            printf("%-10s | %-24s | %-22.22s | %12.2f | %10.0f | %s\n",
                   e.date, categories[e.category], e.description, e.amount,
                   e.odometer, e.frequency == 1 ? "Mensual" :
                   (e.frequency == 2 ? "Anual" : "Unico"));
            count++;
        }
    }
    fclose(f);
    printf("Registros encontrados: %d\n", count);
}

void show_report(void) {
    FILE *f = fopen(DATA_FILE, "r");
    char line[MAX_LINE];
    Expense e;
    double monthly = 0.0, annual = 0.0, total_recorded = 0.0;
    double by_category[CATEGORY_COUNT] = {0};
    int count = 0, i;
    if (!f) { printf("Todavia no hay gastos para calcular.\n"); return; }
    while (fgets(line, sizeof line, f)) {
        if (parse_expense(line, &e)) {
            double m = monthly_cost(&e);
            monthly += m;
            annual += m * 12.0;
            total_recorded += e.amount;
            by_category[e.category] += m;
            count++;
        }
    }
    fclose(f);
    printf("\n========== RESUMEN DE COSTOS ==========\n");
    printf("Registros: %d\n", count);
    printf("Suma de montos registrados: RD$ %.2f\n", total_recorded);
    printf("Costo mensual estimado:      RD$ %.2f\n", monthly);
    printf("Costo anual estimado:        RD$ %.2f\n", annual);
    printf("\nCosto mensual estimado por categoria:\n");
    for (i = 0; i < CATEGORY_COUNT; i++)
        if (by_category[i] > 0)
            printf("  %-25s RD$ %10.2f\n", categories[i], by_category[i]);
    printf("\nNota: los pagos unicos se distribuyen entre 12 meses como estimacion.\n");
}

int main(void) {
    int option;
    do {
        printf("\n========================================\n");
        printf("     GESTION DE COSTOS DE VEHICULO\n");
        printf("========================================\n");
        printf("1. Registrar datos del vehiculo\n");
        printf("2. Consultar datos del vehiculo\n");
        printf("3. Registrar gasto\n");
        printf("4. Consultar gastos\n");
        printf("5. Calcular resumen de costos\n");
        printf("0. Salir\n");
        option = read_int("Seleccione una opcion: ", 0, 5);
        switch (option) {
            case 1: register_vehicle(); break;
            case 2: load_vehicle(); break;
            case 3: add_expense(); break;
            case 4: list_expenses(); break;
            case 5: show_report(); break;
            case 0: printf("Hasta luego.\n"); break;
        }
    } while (option != 0);
    return 0;
}
