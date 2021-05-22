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
/*--- MACROS ---*/
#define ENTRYS 4
#define BUF 50
#define MAX_ROWS 5

//Global Variable:
static GtkEntry *entry[ENTRYS]; //    Textfields - GtkEntry
ListPersons_t *list = NULL;
ListPersons_t *active_P = NULL;
ListPersons_t *completed_P = NULL;
ListRows_t *row_ = NULL;
ListRows_t **rows_ = NULL;

// Enum for the arrival combobox
enum
{
	COLUMN_CHAR,
	COLUMN_STRING,
	N_COLUMNS
};

static void end(GtkWidget *widget, gpointer data)
{
	g_print("Good Bye!\n");
	gtk_main_quit();
}

/* Evaluation input fields */
static void entry_evaluation()
{
	char *first_name, *last_name, arrival; //, *seat;
	unsigned short num = 0;
	Person_t *person = NULL;

	g_object_get(entry[0], "text", &first_name, NULL);
	g_object_get(entry[1], "text", &last_name, NULL);
	//   g_object_get(entry[2], "text", &arrival, NULL);
	//    g_object_get(entry[3], "text", &seat, NULL);
	g_print("Entry-Field Evaluation:\n");
	g_print("First Name   : %s\n", first_name);
	g_print("Last Name   : %s\n", last_name);

	//TODO: Arrival Button mit Combo Boxen belegen "Z" oder "R" soll ausgewählt werden können.

	//TODO: fillStructPerson wird derzeit nicht vollständig befülllt da Arrival fehlt.
	// Diese Funktion wird mit den Combo Boxen implementiert.
	//TODO: Rückgabewert von fillStructPerson muss noch geändert werden
	fillStructPerson(num, arrival, first_name, last_name);
	//      fillStructPersonMan(ListPersons_t *list);

	addPerson(list, person);
	movePerson(list);
	freeListPersons(list);
	printListPersons(list);
	exportListPersons(list);

	//TODO: Seat/Row kein Textfeld sondern soll durch den Button NEw Patient angestoßen werden.

	createRow();
	occupySeat(row_, person); //TODO: Segmentation Fault
							  // int assignSeat(ListRows_t *row, Person_t *person);
	selectRow(rows_, person);

	//   g_print("Seat/Row      : %s\n", seat);
	//   g_print("---------------------------\n");
}

int gui_main(int argc, char **argv, ListPersons_t *active, ListPersons_t *completed, ListRows_t **rows)
{
	active_P = active;
	completed_P = completed;
	rows_ = rows;

	GtkWindow *win;
	GdkPixbuf *pic;
	GtkGrid *table; //Pack widgets in rows and columns
	GtkLabel *label[ENTRYS];
	GtkButton *entry_button[3];
	GtkWidget *hbox, *hbox_2, *hbox_3, *hbox_vscale; //Base class for all widgets
	GtkWidget *vbox, *vbox_spin;					 //Base class for all widgets
	GtkWidget *hsep;
	GtkWidget *arrival_combobox;	  // the combo-box widget, it is easier to cast to other types from Widget instead of other way around
	GtkListStore *arrival_list_store; // Storage for the arrival types & strings
	GtkTreeIter iterator;			  // required for the list storage to set rows
	guint i;
	gchar buf[BUF];

	gtk_init(&argc, &argv);
	// Load a graphic into a pixbuf
	pic = gdk_pixbuf_new_from_file("icon/a.gif", NULL);
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

	// Create list storage for combobox (Only need 2 entries)
	arrival_list_store = gtk_list_store_new(N_COLUMNS, G_TYPE_CHAR, G_TYPE_STRING);
	gchar arrival_type[2] = {'Z', 'R'};
	gchar *arrival_type_string[2] = {"Zivil", "Rettung"};
	// gchar arrival_Z = 'Z';
	// gchar arrival_R = 'R';
	for (int i = 0; i < 2; i++)
	{
		gtk_list_store_append(arrival_list_store, &iterator);
		gtk_list_store_set(arrival_list_store, &iterator,
						   COLUMN_CHAR, arrival_type[i],
						   COLUMN_STRING, arrival_type_string[i],
						   -1);
	}
	// gtk_combo_box_set_model(GTK_COMBO_BOX(arrival_combobox), GTK_TREE_MODEL(arrival_list_store));
	// Create combobox to set arrival type
	arrival_combobox = gtk_combo_box_new_with_model_and_entry(GTK_TREE_MODEL(arrival_list_store));
	gtk_combo_box_set_entry_text_column(GTK_COMBO_BOX(arrival_combobox), COLUMN_STRING);

	// Create horizontal line
	hsep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

	// Create Signalhandler for closing program
	g_signal_connect(win, "destroy",
					 G_CALLBACK(end), NULL);

	// Signalhandler for the Buttons
	g_signal_connect(entry_button[0], "clicked", G_CALLBACK(entry_evaluation), NULL);
	//	g_signal_connect(entry_button[1], "clicked", G_CALLBACK(entry_loeschen), NULL);
	g_signal_connect(entry_button[2], "clicked", G_CALLBACK(entry_evaluation), NULL);

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
	// Old entries = checkboxes for arrival type
	// gtk_grid_attach(table, GTK_WIDGET(entry[2]), 1, 3, 1, 1);
	// gtk_grid_attach(table, GTK_WIDGET(entry[3]), 1, 4, 1, 1);

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
																					 //	gtk_box_pack_start(GTK_BOX(hbox), GTK_WIDGET(entry_button[1]), FALSE, FALSE, 0); //Reset Button
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
