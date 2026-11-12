#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "gastos.csv"
#define VEHICLE_FILE "vehiculo.txt"
#define CATEGORY_COUNT 14

static const char *categories[CATEGORY_COUNT] = {
    "Seguro", "Marbete", "Revista vehicular", "Prestamo",
    "Depreciacion", "Impuestos y permisos", "Parqueo mensual",
    "Combustible", "Mantenimiento", "Neumaticos", "Aceite",
    "Reparaciones", "Estacionamiento por horas", "Lavado"
};

typedef struct {
    GtkWidget *date, *category, *description, *amount, *odometer, *frequency;
    GtkWidget *vehicle_brand, *vehicle_model, *vehicle_year, *vehicle_plate;
    GtkWidget *list, *summary;
} App;

static GtkWidget *entry_new(const char *placeholder) {
    GtkWidget *w = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(w), placeholder);
    return w;
}

static void show_message(GtkWindow *parent, GtkMessageType type, const char *msg) {
    GtkWidget *d = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL, type,
        GTK_BUTTONS_OK, "%s", msg);
    gtk_dialog_run(GTK_DIALOG(d));
    gtk_widget_destroy(d);
}

static void save_vehicle(GtkButton *button, gpointer data) {
    App *a = data;
    FILE *f = fopen(VEHICLE_FILE, "w");
    if (!f) { show_message(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), GTK_MESSAGE_ERROR, "No se pudo guardar vehiculo.txt"); return; }
    fprintf(f, "Marca: %s\nModelo: %s\nAno: %s\nPlaca: %s\n",
        gtk_entry_get_text(GTK_ENTRY(a->vehicle_brand)),
        gtk_entry_get_text(GTK_ENTRY(a->vehicle_model)),
        gtk_entry_get_text(GTK_ENTRY(a->vehicle_year)),
        gtk_entry_get_text(GTK_ENTRY(a->vehicle_plate)));
    fclose(f);
    show_message(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), GTK_MESSAGE_INFO, "Datos del vehiculo guardados.");
}

static void add_expense(GtkButton *button, gpointer data) {
    App *a = data;
    FILE *f;
    const char *date = gtk_entry_get_text(GTK_ENTRY(a->date));
    const char *desc = gtk_entry_get_text(GTK_ENTRY(a->description));
    const char *amount_text = gtk_entry_get_text(GTK_ENTRY(a->amount));
    const char *km_text = gtk_entry_get_text(GTK_ENTRY(a->odometer));
    char *end;
    double amount = g_ascii_strtod(amount_text, &end);
    double km = g_ascii_strtod(km_text, NULL);
    int cat = gtk_combo_box_get_active(GTK_COMBO_BOX(a->category));
    int freq = gtk_combo_box_get_active(GTK_COMBO_BOX(a->frequency)) + 1;

    if (!date[0] || !desc[0] || cat < 0 || amount <= 0 || end == amount_text || *end != '\0') {
        show_message(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), GTK_MESSAGE_WARNING,
                     "Complete fecha, categoria, descripcion y un monto valido.");
        return;
    }
    f = fopen(DATA_FILE, "a");
    if (!f) { show_message(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), GTK_MESSAGE_ERROR, "No se pudo abrir gastos.csv"); return; }
    fprintf(f, "%s;%d;%s;%.2f;%.2f;%d\n", date, cat, desc, amount, km, freq);
    fclose(f);
    show_message(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), GTK_MESSAGE_INFO, "Gasto registrado correctamente.");
}

static void refresh_list(GtkButton *button, gpointer data) {
    App *a = data;
    FILE *f = fopen(DATA_FILE, "r");
    char line[512], output[20000] = "";
    if (!f) { gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(a->list)),
        "No hay gastos registrados todavia.", -1); return; }
    while (fgets(line, sizeof line, f)) {
        g_strlcat(output, line, sizeof output);
    }
    fclose(f);
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(a->list)),
        output[0] ? output : "No hay gastos registrados.", -1);
}

static void show_summary(GtkButton *button, gpointer data) {
    App *a = data;
    FILE *f = fopen(DATA_FILE, "r");
    char line[512], msg[2048];
    double monthly = 0, annual = 0, total = 0;
    int count = 0;
    if (f) {
        while (fgets(line, sizeof line, f)) {
            char date[32], desc[160];
            int cat, freq;
            double amount, km;
            if (sscanf(line, "%31[^;];%d;%159[^;];%lf;%lf;%d",
                       date, &cat, desc, &amount, &km, &freq) == 6 &&
                cat >= 0 && cat < CATEGORY_COUNT && amount > 0) {
                double m = (freq == 1) ? amount : amount / 12.0;
                monthly += m; annual += m * 12.0; total += amount; count++;
            }
        }
        fclose(f);
    }
    g_snprintf(msg, sizeof msg,
        "Registros: %d\nMontos registrados: RD$ %.2f\nCosto mensual estimado: RD$ %.2f\nCosto anual estimado: RD$ %.2f\n\nLos pagos anuales y unicos se distribuyen entre 12 meses como estimacion.",
        count, total, monthly, annual);
    gtk_label_set_text(GTK_LABEL(a->summary), msg);
}

static GtkWidget *make_labeled_row(const char *label, GtkWidget *control) {
    GtkWidget *row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    GtkWidget *l = gtk_label_new(label);
    gtk_widget_set_size_request(l, 145, -1);
    gtk_widget_set_halign(l, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(row), l, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(row), control, TRUE, TRUE, 0);
    return row;
}

static void activate(GtkApplication *app, gpointer user_data) {
    App *a = g_new0(App, 1);
    GtkWidget *window = gtk_application_window_new(app);
    GtkWidget *root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *header = gtk_label_new(NULL);
    GtkWidget *notebook = gtk_notebook_new();
    GtkWidget *vehicle_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    GtkWidget *expense_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    GtkWidget *report_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    GtkWidget *list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    GtkWidget *button, *scroll, *textview;
    int i;

    gtk_window_set_title(GTK_WINDOW(window), "Gestion de Costos de Vehiculo");
    gtk_window_set_default_size(GTK_WINDOW(window), 760, 620);
    gtk_container_set_border_width(GTK_CONTAINER(root), 16);
    gtk_label_set_markup(GTK_LABEL(header), "<span size='xx-large' weight='bold'>AUTO COST MANAGER</span>\nSistema de gestion de costos vehiculares");
    gtk_box_pack_start(GTK_BOX(root), header, FALSE, FALSE, 8);
    gtk_box_pack_start(GTK_BOX(root), notebook, TRUE, TRUE, 0);

    a->vehicle_brand = entry_new("Ej. Toyota");
    a->vehicle_model = entry_new("Ej. Corolla");
    a->vehicle_year = entry_new("Ej. 2018");
    a->vehicle_plate = entry_new("Ej. A123456");
    gtk_box_pack_start(GTK_BOX(vehicle_box), make_labeled_row("Marca:", a->vehicle_brand), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vehicle_box), make_labeled_row("Modelo:", a->vehicle_model), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vehicle_box), make_labeled_row("Ano:", a->vehicle_year), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vehicle_box), make_labeled_row("Placa:", a->vehicle_plate), FALSE, FALSE, 0);
    button = gtk_button_new_with_label("Guardar vehiculo");
    g_signal_connect(button, "clicked", G_CALLBACK(save_vehicle), a);
    gtk_box_pack_start(GTK_BOX(vehicle_box), button, FALSE, FALSE, 6);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vehicle_box, gtk_label_new("Vehiculo"));

    a->date = entry_new("AAAA-MM-DD");
    a->category = gtk_combo_box_text_new();
    for (i = 0; i < CATEGORY_COUNT; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(a->category), categories[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(a->category), 0);
    a->description = entry_new("Descripcion del gasto");
    a->amount = entry_new("Monto en RD$");
    a->odometer = entry_new("Kilometraje (opcional; 0 si no aplica)");
    a->frequency = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(a->frequency), "Mensual");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(a->frequency), "Anual");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(a->frequency), "Pago unico");
    gtk_combo_box_set_active(GTK_COMBO_BOX(a->frequency), 0);
    gtk_box_pack_start(GTK_BOX(expense_box), make_labeled_row("Fecha:", a->date), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(expense_box), make_labeled_row("Categoria:", a->category), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(expense_box), make_labeled_row("Descripcion:", a->description), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(expense_box), make_labeled_row("Monto (RD$):", a->amount), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(expense_box), make_labeled_row("Kilometraje:", a->odometer), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(expense_box), make_labeled_row("Frecuencia:", a->frequency), FALSE, FALSE, 0);
    button = gtk_button_new_with_label("Registrar gasto");
    g_signal_connect(button, "clicked", G_CALLBACK(add_expense), a);
    gtk_box_pack_start(GTK_BOX(expense_box), button, FALSE, FALSE, 8);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), expense_box, gtk_label_new("Registrar gasto"));

    a->summary = gtk_label_new("Presione el boton para calcular los costos.");
    gtk_label_set_xalign(GTK_LABEL(a->summary), 0.0);
    button = gtk_button_new_with_label("Calcular resumen");
    g_signal_connect(button, "clicked", G_CALLBACK(show_summary), a);
    gtk_box_pack_start(GTK_BOX(report_box), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(report_box), a->summary, FALSE, FALSE, 8);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), report_box, gtk_label_new("Resumen"));

    textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview), FALSE);
    a->list = textview;
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), textview);
    button = gtk_button_new_with_label("Actualizar lista");
    g_signal_connect(button, "clicked", G_CALLBACK(refresh_list), a);
    gtk_box_pack_start(GTK_BOX(list_box), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(list_box), scroll, TRUE, TRUE, 0);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), list_box, gtk_label_new("Ver gastos"));

    gtk_container_add(GTK_CONTAINER(window), root);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.autocostmanager", G_APPLICATION_FLAGS_NONE);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
