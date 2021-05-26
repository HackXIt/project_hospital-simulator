#ifndef GTK3_H
#define GTK3_H
#include "hospital_structures.h"
#include <gtk/gtk.h>

typedef struct gtk_patient_info
{
    GtkWidget *first_name_entry;
    GtkWidget *last_name_entry;
    GtkWidget *arrival_combobox;
    ListPersons_t *active_persons;
    ListPersons_t *completed_persons;
    ListRows_t **rows;
} gtk_patient_info_t;


char get_arrival_type_from_combobox(GtkComboBoxText *combobox);
static void on_destroy(GtkWidget *widget, gpointer data);
static void on_new_Patient_clicked(GtkButton *button, gpointer data);
static void on_next_Patient_clicked(GtkButton *button, gpointer data);


int gui_main(int argc, char **argv, ListPersons_t *active, ListPersons_t *completed, ListRows_t **rows);
#endif