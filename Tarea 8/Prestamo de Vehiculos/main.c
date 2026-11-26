#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARCHIVO_JSON "prestamos_vehiculos.json"
#define MAX_CADENA 128

typedef struct Abono {
    double monto;
    char fecha[20];
    struct Abono *siguiente;
} Abono;

typedef struct CuotaMes {
    int numero_mes;
    char etiqueta_mes[24]; /* Ej: "Mes 01" o "2026-12" */
    double monto_cuota;
    int pagado;          /* 1 = Pagado, 0 = No pagado */
    char fecha_pago[20];
    struct CuotaMes *siguiente;
} CuotaMes;

typedef struct Prestamo {
    int id_prestamo;
    char marca[MAX_CADENA];
    char modelo[MAX_CADENA];
    int anio;
    double monto_total;
    double saldo_actual;
    int plazo_meses;
    CuotaMes *cuotas;
    Abono *abonos;
    struct Prestamo *siguiente;
} Prestamo;

typedef struct Cliente {
    int id_cliente;
    char nombre[MAX_CADENA];
    char telefono[32];
    Prestamo *prestamos;
    struct Cliente *siguiente;
} Cliente;

/* --- Utilidades de entrada y cadenas --- */
static void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void leer_linea(const char *prompt, char *destino, size_t tam) {
    printf("%s", prompt);
    if (fgets(destino, (int)tam, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    } else {
        destino[0] = '\0';
    }
}

static int leer_entero(const char *prompt) {
    int valor;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &valor) == 1) {
            limpiar_buffer();
            return valor;
        }
        printf("Entrada invalida. Ingrese un numero entero.\n");
        limpiar_buffer();
    }
}

static double leer_double(const char *prompt) {
    double valor;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &valor) == 1) {
            limpiar_buffer();
            return valor;
        }
        printf("Entrada invalida. Ingrese un numero.\n");
        limpiar_buffer();
    }
}

/* --- Creación y liberación de memoria dinámica --- */
static CuotaMes *crear_cuota(int num_mes, double monto_cuota) {
    CuotaMes *c = (CuotaMes *)calloc(1, sizeof(CuotaMes));
    if (!c) return NULL;
    c->numero_mes = num_mes;
    snprintf(c->etiqueta_mes, sizeof(c->etiqueta_mes), "Mes %02d", num_mes);
    c->monto_cuota = monto_cuota;
    c->pagado = 0;
    strcpy(c->fecha_pago, "-");
    c->siguiente = NULL;
    return c;
}

static Abono *crear_abono(double monto, const char *fecha) {
    Abono *a = (Abono *)calloc(1, sizeof(Abono));
    if (!a) return NULL;
    a->monto = monto;
    strncpy(a->fecha, fecha, sizeof(a->fecha) - 1);
    a->siguiente = NULL;
    return a;
}

static Prestamo *crear_prestamo(int id_prestamo, const char *marca, const char *modelo,
                                int anio, double monto_total, int plazo_meses) {
    Prestamo *p = (Prestamo *)calloc(1, sizeof(Prestamo));
    if (!p) return NULL;
    p->id_prestamo = id_prestamo;
    strncpy(p->marca, marca, MAX_CADENA - 1);
    strncpy(p->modelo, modelo, MAX_CADENA - 1);
    p->anio = anio;
    p->monto_total = monto_total;
    p->saldo_actual = monto_total;
    p->plazo_meses = plazo_meses;

    double cuota_base = (plazo_meses > 0) ? (monto_total / plazo_meses) : 0.0;
    CuotaMes *cabeza = NULL, *cola = NULL;
    for (int i = 1; i <= plazo_meses; i++) {
        CuotaMes *nueva = crear_cuota(i, cuota_base);
        if (!nueva) break;
        if (!cabeza) {
            cabeza = cola = nueva;
        } else {
            cola->siguiente = nueva;
            cola = nueva;
        }
    }
    p->cuotas = cabeza;
    p->abonos = NULL;
    p->siguiente = NULL;
    return p;
}

static Cliente *crear_cliente(int id_cliente, const char *nombre, const char *telefono) {
    Cliente *cl = (Cliente *)calloc(1, sizeof(Cliente));
    if (!cl) return NULL;
    cl->id_cliente = id_cliente;
    strncpy(cl->nombre, nombre, MAX_CADENA - 1);
    strncpy(cl->telefono, telefono, sizeof(cl->telefono) - 1);
    cl->prestamos = NULL;
    cl->siguiente = NULL;
    return cl;
}

static void liberar_prestamo(Prestamo *p) {
    while (p) {
        Prestamo *sig_p = p->siguiente;
        CuotaMes *c = p->cuotas;
        while (c) {
            CuotaMes *sig_c = c->siguiente;
            free(c);
            c = sig_c;
        }
        Abono *a = p->abonos;
        while (a) {
            Abono *sig_a = a->siguiente;
            free(a);
            a = sig_a;
        }
        free(p);
        p = sig_p;
    }
}

static void liberar_todos_clientes(Cliente *cabeza) {
    while (cabeza) {
        Cliente *sig = cabeza->siguiente;
        liberar_prestamo(cabeza->prestamos);
        free(cabeza);
        cabeza = sig;
    }
}

/* --- Operaciones sobre clientes y préstamos --- */
static Cliente *buscar_cliente_por_id(Cliente *cabeza, int id) {
    for (Cliente *cur = cabeza; cur != NULL; cur = cur->siguiente) {
        if (cur->id_cliente == id) return cur;
    }
    return NULL;
}

static void agregar_cliente(Cliente **cabeza) {
    int id = leer_entero("ID del cliente: ");
    if (buscar_cliente_por_id(*cabeza, id) != NULL) {
        printf("Ya existe un cliente con el ID %d.\n", id);
        return;
    }
    char nombre[MAX_CADENA], telefono[32];
    leer_linea("Nombre completo: ", nombre, sizeof(nombre));
    leer_linea("Telefono: ", telefono, sizeof(telefono));

    Cliente *nuevo = crear_cliente(id, nombre, telefono);
    if (!nuevo) {
        printf("Error al asignar memoria para el cliente.\n");
        return;
    }
    nuevo->siguiente = *cabeza;
    *cabeza = nuevo;
    printf("Cliente agregado correctamente.\n");
}

static void buscar_cliente_menu(Cliente *cabeza) {
    printf("1. Buscar por ID\n2. Buscar por nombre\n");
    int op = leer_entero("Opcion: ");
    int encontrados = 0;

    if (op == 1) {
        int id = leer_entero("Ingrese ID: ");
        Cliente *c = buscar_cliente_por_id(cabeza, id);
        if (c) {
            printf("ID: %d | Nombre: %s | Tel: %s\n", c->id_cliente, c->nombre, c->telefono);
            for (Prestamo *p = c->prestamos; p; p = p->siguiente) {
                printf("  -> Prestamo #%d: %s %s (%d) | Saldo: %.2f\n",
                       p->id_prestamo, p->marca, p->modelo, p->anio, p->saldo_actual);
            }
            encontrados = 1;
        }
    } else {
        char consulta[MAX_CADENA];
        leer_linea("Ingrese texto del nombre: ", consulta, sizeof(consulta));
        for (Cliente *c = cabeza; c != NULL; c = c->siguiente) {
            if (strstr(c->nombre, consulta) != NULL) {
                printf("ID: %d | Nombre: %s | Tel: %s\n", c->id_cliente, c->nombre, c->telefono);
                encontrados++;
            }
        }
    }
    if (!encontrados) {
        printf("No se encontraron clientes coincidentes.\n");
    }
}

static void borrar_cliente(Cliente **cabeza) {
    int id = leer_entero("ID del cliente a borrar: ");
    Cliente *cur = *cabeza, *prev = NULL;
    while (cur != NULL && cur->id_cliente != id) {
        prev = cur;
        cur = cur->siguiente;
    }
    if (!cur) {
        printf("Cliente no encontrado.\n");
        return;
    }
    if (!prev) {
        *cabeza = cur->siguiente;
    } else {
        prev->siguiente = cur->siguiente;
    }
    liberar_prestamo(cur->prestamos);
    free(cur);
    printf("Cliente %d y sus prestamos asociados eliminados.\n", id);
}

static Prestamo *buscar_prestamo(Cliente *cabeza, int id_prestamo, Cliente **dueno_out) {
    for (Cliente *c = cabeza; c != NULL; c = c->siguiente) {
        for (Prestamo *p = c->prestamos; p != NULL; p = p->siguiente) {
            if (p->id_prestamo == id_prestamo) {
                if (dueno_out) *dueno_out = c;
                return p;
            }
        }
    }
    return NULL;
}

static void crear_prestamo_vehiculo(Cliente *cabeza) {
    int id_cli = leer_entero("ID del cliente: ");
    Cliente *cli = buscar_cliente_por_id(cabeza, id_cli);
    if (!cli) {
        printf("Cliente no encontrado. Registre el cliente primero.\n");
        return;
    }

    int id_p = leer_entero("ID del prestamo: ");
    if (buscar_prestamo(cabeza, id_p, NULL) != NULL) {
        printf("Ya existe un prestamo con ese ID.\n");
        return;
    }

    char marca[MAX_CADENA], modelo[MAX_CADENA];
    leer_linea("Marca del vehiculo: ", marca, sizeof(marca));
    leer_linea("Modelo del vehiculo: ", modelo, sizeof(modelo));
    int anio = leer_entero("Ano del vehiculo: ");
    double monto = leer_double("Monto del prestamo: ");
    int plazo = leer_entero("Plazo en meses: ");

    if (monto <= 0.0 || plazo <= 0) {
        printf("Monto y plazo deben ser mayores que cero.\n");
        return;
    }

    Prestamo *p = crear_prestamo(id_p, marca, modelo, anio, monto, plazo);
    if (!p) {
        printf("Error de memoria al crear prestamo.\n");
        return;
    }
    p->siguiente = cli->prestamos;
    cli->prestamos = p;
    printf("Prestamo vehicular #%d creado para %s.\n", id_p, cli->nombre);
}

static void gestionar_pago_mensual(Cliente *cabeza) {
    int id_p = leer_entero("ID del prestamo: ");
    Prestamo *p = buscar_prestamo(cabeza, id_p, NULL);
    if (!p) {
        printf("Prestamo no encontrado.\n");
        return;
    }

    int num_mes = leer_entero("Numero de mes a marcar como pagado: ");
    CuotaMes *c = p->cuotas;
    while (c && c->numero_mes != num_mes) {
        c = c->siguiente;
    }
    if (!c) {
        printf("Mes %d fuera del plazo (%d meses).\n", num_mes, p->plazo_meses);
        return;
    }
    if (c->pagado) {
        printf("El %s ya figura como pagado (%s).\n", c->etiqueta_mes, c->fecha_pago);
        return;
    }

    char fecha[20];
    leer_linea("Fecha de pago (YYYY-MM-DD): ", fecha, sizeof(fecha));
    c->pagado = 1;
    strncpy(c->fecha_pago, fecha, sizeof(c->fecha_pago) - 1);

    p->saldo_actual -= c->monto_cuota;
    if (p->saldo_actual < 0.0) p->saldo_actual = 0.0;

    printf("Pago mensual de %s registrado. Nuevo saldo: %.2f\n", c->etiqueta_mes, p->saldo_actual);
}

static void agregar_pago_abono(Cliente *cabeza) {
    int id_p = leer_entero("ID del prestamo: ");
    Prestamo *p = buscar_prestamo(cabeza, id_p, NULL);
    if (!p) {
        printf("Prestamo no encontrado.\n");
        return;
    }
    if (p->saldo_actual <= 0.0) {
        printf("El prestamo ya tiene saldo 0.00.\n");
        return;
    }

    double monto = leer_double("Monto del abono: ");
    if (monto <= 0.0 || monto > p->saldo_actual) {
        printf("Monto invalido. Debe ser mayor que 0 y menor o igual al saldo (%.2f).\n", p->saldo_actual);
        return;
    }

    char fecha[20];
    leer_linea("Fecha del abono (YYYY-MM-DD): ", fecha, sizeof(fecha));

    Abono *ab = crear_abono(monto, fecha);
    if (!ab) {
        printf("Error al asignar memoria para el abono.\n");
        return;
    }
    ab->siguiente = p->abonos;
    p->abonos = ab;

    p->saldo_actual -= monto;
    if (p->saldo_actual < 0.0) p->saldo_actual = 0.0;

    printf("Abono de %.2f aplicado. Saldo restante: %.2f\n", monto, p->saldo_actual);
}

static void generar_reporte_estado_pago(Cliente *cabeza) {
    int id_p = leer_entero("ID del prestamo para reporte: ");
    Cliente *cli = NULL;
    Prestamo *p = buscar_prestamo(cabeza, id_p, &cli);
    if (!p || !cli) {
        printf("Prestamo no encontrado.\n");
        return;
    }

    printf("\n================ REPORTE DE ESTADO DE PAGO ================\n");
    printf("Cliente : %s (ID %d) | Tel: %s\n", cli->nombre, cli->id_cliente, cli->telefono);
    printf("Vehiculo: %s %s (Ano %d) | Prestamo #%d\n", p->marca, p->modelo, p->anio, p->id_prestamo);
    printf("Monto original: %.2f | Plazo: %d meses\n", p->monto_total, p->plazo_meses);
    printf("-----------------------------------------------------------\n");
    printf("%-10s %-14s %-12s %-12s\n", "MES", "ESTADO", "CUOTA", "FECHA PAGO");
    printf("-----------------------------------------------------------\n");

    for (CuotaMes *c = p->cuotas; c != NULL; c = c->siguiente) {
        printf("%-10s %-14s %-12.2f %-12s\n",
               c->etiqueta_mes,
               c->pagado ? "PAGADO" : "NO PAGADO",
               c->monto_cuota,
               c->pagado ? c->fecha_pago : "-");
    }

    printf("-----------------------------------------------------------\n");
    double total_abonos = 0.0;
    for (Abono *a = p->abonos; a != NULL; a = a->siguiente) {
        total_abonos += a->monto;
    }
    printf("Total abonos registrados: %.2f\n", total_abonos);
    printf("SALDO ACTUAL: %.2f\n", p->saldo_actual);
    printf("===========================================================\n\n");
}

/* --- Persistencia JSON --- */
static void escribir_json_escapado(FILE *f, const char *s) {
    fputc('"', f);
    for (const char *p = s; *p; p++) {
        if (*p == '"' || *p == '\\') {
            fputc('\\', f);
        }
        fputc(*p, f);
    }
    fputc('"', f);
}

static void guardar_json(Cliente *cabeza, const char *ruta) {
    FILE *f = fopen(ruta, "w");
    if (!f) {
        printf("No se pudo abrir %s para escritura.\n", ruta);
        return;
    }

    fprintf(f, "{\n  \"clientes\": [\n");
    for (Cliente *c = cabeza; c != NULL; c = c->siguiente) {
        fprintf(f, "    {\n");
        fprintf(f, "      \"id_cliente\": %d,\n", c->id_cliente);
        fprintf(f, "      \"nombre\": "); escribir_json_escapado(f, c->nombre); fprintf(f, ",\n");
        fprintf(f, "      \"telefono\": "); escribir_json_escapado(f, c->telefono); fprintf(f, ",\n");
        fprintf(f, "      \"prestamos\": [\n");

        for (Prestamo *p = c->prestamos; p != NULL; p = p->siguiente) {
            fprintf(f, "        {\n");
            fprintf(f, "          \"id_prestamo\": %d,\n", p->id_prestamo);
            fprintf(f, "          \"marca\": "); escribir_json_escapado(f, p->marca); fprintf(f, ",\n");
            fprintf(f, "          \"modelo\": "); escribir_json_escapado(f, p->modelo); fprintf(f, ",\n");
            fprintf(f, "          \"anio\": %d,\n", p->anio);
            fprintf(f, "          \"monto_total\": %.2f,\n", p->monto_total);
            fprintf(f, "          \"saldo_actual\": %.2f,\n", p->saldo_actual);
            fprintf(f, "          \"plazo_meses\": %d,\n", p->plazo_meses);
            fprintf(f, "          \"cuotas\": [\n");

            for (CuotaMes *cu = p->cuotas; cu != NULL; cu = cu->siguiente) {
                fprintf(f, "            {\"numero_mes\": %d, \"etiqueta_mes\": ", cu->numero_mes);
                escribir_json_escapado(f, cu->etiqueta_mes);
                fprintf(f, ", \"monto_cuota\": %.2f, \"pagado\": %d, \"fecha_pago\": ",
                        cu->monto_cuota, cu->pagado);
                escribir_json_escapado(f, cu->fecha_pago);
                fprintf(f, "}%s\n", cu->siguiente ? "," : "");
            }
            fprintf(f, "          ],\n");
            fprintf(f, "          \"abonos\": [\n");
            for (Abono *ab = p->abonos; ab != NULL; ab = ab->siguiente) {
                fprintf(f, "            {\"monto\": %.2f, \"fecha\": ", ab->monto);
                escribir_json_escapado(f, ab->fecha);
                fprintf(f, "}%s\n", ab->siguiente ? "," : "");
            }
            fprintf(f, "          ]\n");
            fprintf(f, "        }%s\n", p->siguiente ? "," : "");
        }
        fprintf(f, "      ]\n");
        fprintf(f, "    }%s\n", c->siguiente ? "," : "");
    }
    fprintf(f, "  ]\n}\n");
    fclose(f);
    printf("Datos guardados en %s.\n", ruta);
}

/* Parser sencillo orientado a claves del formato generado por guardar_json */
static const char *saltar_espacios(const char *s) {
    while (*s && isspace((unsigned char)*s)) s++;
    return s;
}

static const char *leer_cadena_json(const char *s, char *out, size_t tam) {
    s = saltar_espacios(s);
    if (*s != '"') return s;
    s++;
    size_t i = 0;
    while (*s && *s != '"') {
        if (*s == '\\' && *(s + 1)) s++;
        if (i + 1 < tam) out[i++] = *s;
        s++;
    }
    out[i] = '\0';
    if (*s == '"') s++;
    return s;
}

static Cliente *cargar_json(const char *ruta) {
    FILE *f = fopen(ruta, "r");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    rewind(f);
    if (tam <= 0) {
        fclose(f);
        return NULL;
    }

    char *buf = (char *)malloc((size_t)tam + 1);
    if (!buf) {
        fclose(f);
        return NULL;
    }
    size_t leidos = fread(buf, 1, (size_t)tam, f);
    buf[leidos] = '\0';
    fclose(f);

    Cliente *cabeza_cli = NULL, *cola_cli = NULL;
    const char *p = buf;

    while ((p = strstr(p, "\"id_cliente\"")) != NULL) {
        p = strchr(p, ':');
        if (!p) break;
        int id_cli = atoi(p + 1);

        char nombre[MAX_CADENA] = "", tel[32] = "";
        const char *k_nom = strstr(p, "\"nombre\"");
        if (k_nom && (k_nom = strchr(k_nom, ':'))) leer_cadena_json(k_nom + 1, nombre, sizeof(nombre));
        const char *k_tel = strstr(p, "\"telefono\"");
        if (k_tel && (k_tel = strchr(k_tel, ':'))) leer_cadena_json(k_tel + 1, tel, sizeof(tel));

        Cliente *cli = crear_cliente(id_cli, nombre, tel);
        if (!cli) break;

        if (!cabeza_cli) cabeza_cli = cola_cli = cli;
        else { cola_cli->siguiente = cli; cola_cli = cli; }

        const char *fin_cli = strstr(p, "\"prestamos\"");
        const char *sig_cli = strstr(p + 1, "\"id_cliente\"");
        const char *limite_cli = sig_cli ? sig_cli : (buf + leidos);

        Prestamo *cabeza_p = NULL, *cola_p = NULL;
        const char *cur_p = fin_cli;
        while (cur_p && cur_p < limite_cli && (cur_p = strstr(cur_p, "\"id_prestamo\"")) != NULL && cur_p < limite_cli) {
            const char *colon = strchr(cur_p, ':');
            if (!colon) break;
            int id_p = atoi(colon + 1);

            char marca[MAX_CADENA] = "", modelo[MAX_CADENA] = "";
            int anio = 0, plazo = 0;
            double monto_total = 0.0, saldo_actual = 0.0;

            const char *k;
            if ((k = strstr(cur_p, "\"marca\"")) && k < limite_cli && (k = strchr(k, ':')))
                leer_cadena_json(k + 1, marca, sizeof(marca));
            if ((k = strstr(cur_p, "\"modelo\"")) && k < limite_cli && (k = strchr(k, ':')))
                leer_cadena_json(k + 1, modelo, sizeof(modelo));
            if ((k = strstr(cur_p, "\"anio\"")) && k < limite_cli && (k = strchr(k, ':')))
                anio = atoi(k + 1);
            if ((k = strstr(cur_p, "\"monto_total\"")) && k < limite_cli && (k = strchr(k, ':')))
                monto_total = atof(k + 1);
            if ((k = strstr(cur_p, "\"saldo_actual\"")) && k < limite_cli && (k = strchr(k, ':')))
                saldo_actual = atof(k + 1);
            if ((k = strstr(cur_p, "\"plazo_meses\"")) && k < limite_cli && (k = strchr(k, ':')))
                plazo = atoi(k + 1);

            Prestamo *pr = crear_prestamo(id_p, marca, modelo, anio, monto_total, plazo);
            if (pr) {
                pr->saldo_actual = saldo_actual;

                const char *sig_p = strstr(cur_p + 1, "\"id_prestamo\"");
                const char *limite_p = (sig_p && sig_p < limite_cli) ? sig_p : limite_cli;

                const char *sec_cuotas = strstr(cur_p, "\"cuotas\"");
                const char *sec_abonos = strstr(cur_p, "\"abonos\"");

                const char *c_ptr = sec_cuotas;
                while (c_ptr && (!sec_abonos || c_ptr < sec_abonos) && c_ptr < limite_p &&
                       (c_ptr = strstr(c_ptr, "\"numero_mes\"")) != NULL && c_ptr < limite_p) {
                    const char *c_col = strchr(c_ptr, ':');
                    int nmes = c_col ? atoi(c_col + 1) : 0;
                    int pag = 0;
                    char fpago[20] = "-";
                    const char *kp = strstr(c_ptr, "\"pagado\"");
                    if (kp && kp < limite_p && (kp = strchr(kp, ':'))) pag = atoi(kp + 1);
                    const char *kf = strstr(c_ptr, "\"fecha_pago\"");
                    if (kf && kf < limite_p && (kf = strchr(kf, ':')))
                        leer_cadena_json(kf + 1, fpago, sizeof(fpago));

                    for (CuotaMes *cm = pr->cuotas; cm; cm = cm->siguiente) {
                        if (cm->numero_mes == nmes) {
                            cm->pagado = pag;
                            strncpy(cm->fecha_pago, fpago, sizeof(cm->fecha_pago) - 1);
                            break;
                        }
                    }
                    c_ptr++;
                }

                Abono *cab_ab = NULL, *cola_ab = NULL;
                const char *a_ptr = sec_abonos;
                while (a_ptr && a_ptr < limite_p &&
                       (a_ptr = strstr(a_ptr, "\"monto\"")) != NULL && a_ptr < limite_p) {
                    const char *a_col = strchr(a_ptr, ':');
                    double mab = a_col ? atof(a_col + 1) : 0.0;
                    char fab[20] = "";
                    const char *kaf = strstr(a_ptr, "\"fecha\"");
                    if (kaf && kaf < limite_p && (kaf = strchr(kaf, ':')))
                        leer_cadena_json(kaf + 1, fab, sizeof(fab));

                    Abono *ab = crear_abono(mab, fab);
                    if (ab) {
                        if (!cab_ab) cab_ab = cola_ab = ab;
                        else { cola_ab->siguiente = ab; cola_ab = ab; }
                    }
                    a_ptr++;
                }
                pr->abonos = cab_ab;

                if (!cabeza_p) cabeza_p = cola_p = pr;
                else { cola_p->siguiente = pr; cola_p = pr; }
            }
            cur_p++;
        }
        cli->prestamos = cabeza_p;
        p = limite_cli;
    }

    free(buf);
    return cabeza_cli;
}

int main(void) {
    Cliente *clientes = cargar_json(ARCHIVO_JSON);
    if (clientes) {
        printf("Datos cargados desde %s.\n", ARCHIVO_JSON);
    }

    int opcion;
    do {
        printf("\n=== PRESTAMOS PARA COMPRA DE VEHICULOS ===\n");
        printf("1. Agregar cliente\n");
        printf("2. Buscar cliente\n");
        printf("3. Borrar cliente\n");
        printf("4. Crear prestamo (Marca, Modelo, Ano)\n");
        printf("5. Gestionar pago mensual\n");
        printf("6. Agregar pago de abono\n");
        printf("7. Generar reporte de estado de pago\n");
        printf("8. Guardar en JSON\n");
        printf("0. Guardar y salir\n");
        opcion = leer_entero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: agregar_cliente(&clientes); break;
            case 2: buscar_cliente_menu(clientes); break;
            case 3: borrar_cliente(&clientes); break;
            case 4: crear_prestamo_vehiculo(clientes); break;
            case 5: gestionar_pago_mensual(clientes); break;
            case 6: agregar_pago_abono(clientes); break;
            case 7: generar_reporte_estado_pago(clientes); break;
            case 8: guardar_json(clientes, ARCHIVO_JSON); break;
            case 0:
                guardar_json(clientes, ARCHIVO_JSON);
                liberar_todos_clientes(clientes);
                printf("Memoria liberada. Hasta pronto.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 0);

    return 0;
}
