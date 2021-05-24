/* MAIN.c
 *   by Nikolaus Rieder, Stefan Bittgen, Eva Grabler
 * Description:
 *   Main execution for the gui
**/

/*--- COMMON LIBRARIES ---*/
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
/*--- CUSTOM LIBRARIES ---*/
#include "gtk3.h"
#include "persons.h"
#include "seat_rows.h"
#include "hospital_structures.h" // Is listed here for completion, but not necessary since gtk3.h includes it
/*--- MACROS ---*/
#define DEBUG
#define ENTRYS 4
#define BUF 50
#define MAX_ROWS 5

// Enum for the arrival combobox
enum
{
	COLUMN_INT,
	COLUMN_CHAR,
	COLUMN_STRING,
	N_COLUMNS
};

typedef struct gtk_patient_info
{
	GtkWidget *first_name_entry;
	GtkWidget *last_name_entry;
	GtkWidget *arrival_combobox;
	ListPersons_t *active_persons;
	ListPersons_t *completed_persons;
	ListRows_t **rows;
} gtk_patient_info_t;

// When using GTK_COMBO_BOX, this implementation is needed to get the arrival_type
/*
char get_arrival_type_from_combobox(GtkComboBox *combobox)
{
	GtkListStore *store;
	GtkTreeIter iter;
	int return_value;
	int row;
	gchar *arrival_string;
	gchar arrival_type;

	return_value = gtk_combo_box_get_active_iter(combobox, &iter);
	// g_print("Return: %i\n", return_value);
	store = GTK_LIST_STORE(gtk_combo_box_get_model(combobox));
	gtk_tree_model_get(GTK_TREE_MODEL(store), &iter,
					   COLUMN_INT, &row,
					   COLUMN_CHAR, &arrival_type,
					   COLUMN_STRING, &arrival_string,
					   -1);
#ifdef DEBUG
	g_print("DEBUG get_arrival_type_from_combobox():\n");
	g_print("element-number: %i\n", row);
	g_print("arrival_string: %s\n", arrival_string);
	g_print("arrival_type: %c\n", arrival_type);
#endif
	return arrival_type;
}
*/
// When using GTK_COMBO_BOX_TEXT, this implementation is needed to get the arrival_type
char get_arrival_type_from_combobox(GtkComboBoxText *combobox)
{
	char arrival_type;
	int return_value;
	if (g_strcmp0((char *)gtk_combo_box_text_get_active_text(combobox), "Zivil"))
	{
		arrival_type = 'Z';
	}
	else if (g_strcmp0((char *)gtk_combo_box_text_get_active_text(combobox), "Rettung"))
	{
		arrival_type = 'R';
	}
	else
	{
		arrival_type = 0;
	}
	return arrival_type;
}

static void on_destroy(GtkWidget *widget, gpointer data)
{
	g_print("Good Bye!\n");
	gtk_main_quit();
}

/* Evaluation input fields */
static void on_add_Patient_clicked(GtkButton *button, gpointer data)
{
	gtk_patient_info_t *patient_info = data;
	char *first_name;
	char *last_name;
	char arrival;
	unsigned short num = 0;
	Person_t *person = NULL;

#ifdef DEBUG
	// Checking if the provided user_data is set correctly, because the widgets could be NULL
	g_print(GTK_IS_WIDGET(patient_info->first_name_entry) ? "First_Name: true\n" : "First_Name: false\n");
	g_print(GTK_IS_WIDGET(patient_info->last_name_entry) ? "Last_Name: true\n" : "Last_Name: false\n");
	g_print(GTK_IS_WIDGET(patient_info->arrival_combobox) ? "Arrival_Combobox: true\n" : "Arrival_Combobox: false\n");
#endif

	first_name = (char *)gtk_entry_get_text(GTK_ENTRY(patient_info->first_name_entry));
	last_name = (char *)gtk_entry_get_text(GTK_ENTRY(patient_info->last_name_entry));
	// When using GTK_COMBO_BOX, this implementation is needed to get the arrival_type
	// arrival = get_arrival_type_from_combobox(GTK_COMBO_BOX(patient_info->arrival_combobox));
	// When using GTK_COMBO_BOX_TEXT, this implementation is needed to get the arrival_type
	arrival = get_arrival_type_from_combobox(GTK_COMBO_BOX_TEXT(patient_info->arrival_combobox));
	if (arrival == 0)
	{
		fprintf(stderr, "No arrival type was set.\n");
	}

#ifdef DEBUG
	g_print("Entry-Field Evaluation:\n");
	g_print("First Name: %s\n", first_name);
	g_print("Last Name: %s\n", last_name);
	g_print("Arrival: %c\n", arrival);
#endif
	person = fillStructPerson(num, arrival, first_name, last_name);
	if (addPerson(patient_info->active_persons, person) < 0)
	{
		fprintf(stderr, "Failed to add Person.\n");
	}
	if (selectRow(patient_info->rows, person) < 0)
	{
		fprintf(stderr, "Failed to select row.\n");
	}
	g_print("Person hinzugefügt.\n");
}

static void on_next_Patient_clicked(GtkButton *button, gpointer data)
{
	//    TODO Callback for nextPatient

	//    movePerson(active_P, completed_P);
	//    appendPerson(person, list);
	//    printListPerson(list);
	g_print("Not implemented!\n");
}
/*
static void on_arrival_combobox_changed(GtkComboBox *combobox, gpointer data)
{
	g_print("Arrival Type: %c\n", get_arrival_type_from_combobox(combobox));
}
*/

int gui_main(int argc, char **argv, ListPersons_t *active, ListPersons_t *completed, ListRows_t **rows)
{
	gtk_patient_info_t patient_info = {
		.active_persons = active,
		.completed_persons = completed,
		.rows = rows,
		.first_name_entry = NULL,
		.last_name_entry = NULL,
		.arrival_combobox = NULL};
	GtkWindow *win;
	GdkPixbuf *pic;
	GtkGrid *table; //Pack widgets in rows and columns
	GtkLabel *label[ENTRYS];
	GtkEntry *entry[ENTRYS]; //    Textfields - GtkEntry
	GtkButton *entry_button[3];
	GtkWidget *hbox, *hbox_2, *hbox_3, *hbox_vscale; //Base class for all widgets
	GtkWidget *vbox, *vbox_spin;					 //Base class for all widgets
	GtkWidget *hsep;
	GError *err = NULL;
	GtkWidget *arrival_combobox; // the combo-box widget, it is easier to cast to other types from Widget instead of other way around
	// These variables are necessary when using GTK_COMBO_BOX instead of GTK_COMBO_BOX_TEXT
	// GtkListStore *arrival_list_store; // Storage for the arrival types & strings
	// GtkTreeIter iterator;			  // required for the list storage to set rows
	guint i;
	gchar buf[BUF];

	gtk_init(&argc, &argv);
	// Load a graphic into a pixbuf
	const gchar *const icon_name = "Icon.png";
	pic = gdk_pixbuf_new_from_file(icon_name, &err);
	(pic == NULL) ? g_print("The following error is occurred: %s\n", err->message)
				  : gtk_window_set_default_icon(pic);

	// Create window with the following properties:
	win = g_object_new(GTK_TYPE_WINDOW,
					   "title", "Hospital Simulator",
					   "default-width", 380,
					   "default-height", 200,
					   "resizable", TRUE,
					   "window-position", GTK_WIN_POS_CENTER,
					   "border-width", 10,
					   "icon", pic,
					   NULL);
	// Create a table 8x3
	table = GTK_GRID(gtk_grid_new());	   //Creates a new Grid-Widget
	gtk_grid_set_row_spacing(table, 3);	   //Sets the amount of space between rows of grid .
	gtk_grid_set_column_spacing(table, 3); //Sets the amount of space between columns of grid .
	// Create a horizontal box
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10); //Creates a new GTK-Box -> GtkBox — A container for packing widgets in a single row or column
	// Create a second horizontal box
	hbox_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

	// Create a vertical box
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	// Create a vertical box for the number fields
	vbox_spin = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);

	// Creates ENTRYS number fields
	for (i = 0; i < ENTRYS - 2; i++)
	{
		entry[i] = GTK_ENTRY(gtk_entry_new());
		gtk_entry_set_text(entry[i], "Type here ...");
		gtk_entry_set_max_length(entry[i], BUF);
	}

	// Our check button "Zivil"
	g_snprintf(buf, BUF, "Zivil");
	entry[2] = g_object_new(GTK_TYPE_CHECK_BUTTON, "label", buf, NULL);

	//Check button "Rettung"
	g_snprintf(buf, BUF, "Rettung");
	entry[3] = g_object_new(GTK_TYPE_CHECK_BUTTON, "label", buf, NULL);

	// Create labels for text fields
	label[0] = g_object_new(GTK_TYPE_LABEL,
							"justify", GTK_JUSTIFY_LEFT,
							"label", "First Name",
							NULL);
	label[1] = g_object_new(GTK_TYPE_LABEL,
							"justify", GTK_JUSTIFY_LEFT,
							"label", "Last Name",
							NULL);
	label[2] = g_object_new(GTK_TYPE_LABEL,
							"label", "Arrival",
							NULL);

	// Create buttons to evaluate the text fields
	entry_button[0] = g_object_new(GTK_TYPE_BUTTON, "label", "New Patient", NULL);
	//    entry_button[1] = g_object_new( GTK_TYPE_BUTTON,"label", "Reset",NULL );
	entry_button[2] = g_object_new(GTK_TYPE_BUTTON, "label", "Next Patient", NULL);

	gchar *arrival_type_string[] = {"Zivil", "Rettung"};
	arrival_combobox = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(arrival_combobox),
							  NULL,
							  arrival_type_string[0]);
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(arrival_combobox),
							  NULL,
							  arrival_type_string[1]);
	// Create list storage for combobox (Only need 2 entries)
	// arrival_list_store = gtk_list_store_new(N_COLUMNS, G_TYPE_INT, G_TYPE_CHAR, G_TYPE_STRING);
	// char arrival_type[] = {'Z', 'R'};
	// char *arrival_type_string[] = {"Zivil", "Rettung"};
	// // gchar arrival_Z = 'Z';
	// // gchar arrival_R = 'R';
	// for (int i = 0; i < 2; i++)
	// {
	// 	gtk_list_store_append(arrival_list_store, &iterator);
	// 	gtk_list_store_set(arrival_list_store, &iterator,
	// 					   COLUMN_INT, i,
	// 					   COLUMN_CHAR, arrival_type[i],
	// 					   COLUMN_STRING, arrival_type_string[i],
	// 					   -1);
	// }
	// gtk_combo_box_set_model(GTK_COMBO_BOX(arrival_combobox), GTK_TREE_MODEL(arrival_list_store));
	// Create combobox to set arrival type
	// arrival_combobox = gtk_combo_box_new_with_model_and_entry(GTK_TREE_MODEL(arrival_list_store));
	// gtk_combo_box_set_entry_text_column(GTK_COMBO_BOX(arrival_combobox), COLUMN_STRING);
	// g_object_unref(arrival_list_store);

	// Create horizontal line
	hsep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

	// Initialize struct for all the relevant patient_information widgets
	// MUST BE DONE HERE, after initialization of widgets, otherwise the data will be incorrect.
	patient_info.first_name_entry = GTK_WIDGET(entry[0]);
	patient_info.last_name_entry = GTK_WIDGET(entry[1]);
	patient_info.arrival_combobox = arrival_combobox;

	// Create Signalhandler for closing program
	g_signal_connect(win, "destroy",
					 G_CALLBACK(on_destroy), NULL);

	// Signalhandler for the Buttons
	g_signal_connect(entry_button[0], "clicked", G_CALLBACK(on_add_Patient_clicked), &patient_info);
	//	g_signal_connect(entry_button[1], "clicked", G_CALLBACK(entry_loeschen), NULL);
	g_signal_connect(entry_button[2], "clicked", G_CALLBACK(on_next_Patient_clicked), &patient_info);

	// Signalhandler for combobox
	// Not used at the moment
	// g_signal_connect(arrival_combobox, "changed", G_CALLBACK(on_arrival_combobox_changed), &patient_info);

	/* Great packing of the widgets begins
*  Adds a widget to the grid.
*  The position of child is determined by left and top .
*  The number of “cells” that child will occupy is determined by width and height .
*/
	// First name
	gtk_grid_attach(table, GTK_WIDGET(label[0]), 0, 0, 1, 1);
	gtk_grid_attach(table, GTK_WIDGET(entry[0]), 1, 0, 1, 1);
	// Last name
	gtk_grid_attach(table, GTK_WIDGET(label[1]), 0, 2, 1, 1);
	gtk_grid_attach(table, GTK_WIDGET(entry[1]), 1, 2, 1, 1);
	// Arrival
	gtk_grid_attach(table, GTK_WIDGET(label[2]), 0, 3, 1, 1);
	gtk_grid_attach(table, arrival_combobox, 1, 3, 1, 1);

	gtk_grid_attach(table, GTK_WIDGET(hbox), 1, 6, 1, 1);

	/* NOTE GRID-Helper
	1st Number is left
	LEFT_TO_RIGHT
	~~~~~~~~~~~~~~~~~
	| 0 1 2 3 4 5 6 |
	| 0 1 2 3 4 5 6 |
	| 0 1 2 3 4 5 6 |
	| 0 1 2 3 4 5 6 |
	| 0 1 2 3 4 5 6 |
	| 0 1 2 3 4 5 6 |
	~~~~~~~~~~~~~~~~~
	2nd Number is top
	TOP_TO_BOTTOM
	~~~~~~~~~~~~~~~~~
	| 0 0 0 0 0 0 0 |
	| 1 1 1 1 1 1 1 |
	| 2 2 2 2 2 2 2 |
	| 3 3 3 3 3 3 3 |
	| 4 4 4 4 4 4 4 |
	| 5 5 5 5 5 5 5 |
	| 6 6 6 6 6 6 6 |
	~~~~~~~~~~~~~~~~~
	*/

	/* Adds child to box , packed with reference to the start of box .
*  The child is packed after any other child packed with reference to the start of box .
*/

	gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(entry_button[0]), FALSE, FALSE, 0); //New Button

	gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(entry_button[2]), FALSE, FALSE, 0); //Next Button

	gtk_box_pack_start(GTK_BOX(vbox_spin), GTK_WIDGET(hsep), FALSE, FALSE, 0);

	/* Adds widget to container . Typically used for simple containers such as GtkWindow,
 * GtkFrame, or GtkButton; for more complicated layout containers such as GtkBox or GtkGrid,
 * this function will pick default packing parameters that may not be correct.
 *
*/

	gtk_container_add(GTK_CONTAINER(vbox), GTK_WIDGET(hbox_2));
	gtk_container_add(GTK_CONTAINER(hbox_2), GTK_WIDGET(table));
	gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(vbox));

	/* Show the window */
	gtk_widget_show_all(GTK_WIDGET(win));

	/* Mainloop of gtk. Program awaits interaction  */
	gtk_main();
	g_print("The Main loop has been terminated.\n");

	return 0;
}
