/* MAIN.c
 *   by Nikolaus Rieder, Stefan Bittgen, Eva Grabler
 * Description:
 *   Main execution of the project
**/

/*--- COMMON LIBRARIES ---*/
#include <stdio.h>
#include <stdlib.h>
/*--- CUSTOM LIBRARIES ---*/
//#include "gtk3.h"
#include <gtk/gtk.h>
//#include "hospital_structures.h"
#include "persons.h"
#include "seat_rows.h"
/*--- MACROS ---*/
#define VBOX 3
#define SCALES 3
#define SPIN 2
#define ENTRYS 4
#define BUF 50


//Global Variable:
static GtkEntry   *entry[ENTRYS]; //    Textfields - GtkEntry


static gint delete_Event(GtkWidget *widget, GdkEvent event, gpointer daten) {
g_print("Die Anwendung wird beendet.\n");
/* Only with FALSE the application is really terminated */
return FALSE;
}

static void end ( GtkWidget *widget, gpointer data ) {
    g_print("Good Bye!\n");
    gtk_main_quit();
}

/* Evaluation input fields */
static void entry_evaluation(gpointer evalu) {
    gchar *first_name, *last_name, *arrival, *seat;
    unsigned short num;
    ListPersons_t *list;
    Person_t *person;

    g_object_get(entry[0], "text", &first_name, NULL);
    g_object_get(entry[1], "text", &last_name, NULL);
    g_object_get(entry[2], "text", &arrival, NULL);
    g_object_get(entry[3], "text", &seat, NULL);
    g_print("Entry-Field Evaluation:\n");
    //TODO: Statt New Patient, Vorname, Nachname in jeweils eine Zeile. Check!
    g_print("First Name   : %s\n", first_name);
    g_print("Last Name   : %s\n", last_name);
    //TODO: MainTask: Es darf nur "Z" oder "R" angenommen werden. Sonst Fehlermeldung. Check!
    //TODO: Optional: Arrival Button wird aufgerufen und entweder "Z" oder "R" anklicken. Checkboxen vllt
    if (strcmp(arrival, "Z") == 0 || strcmp(arrival, "R") == 0) {
        g_print("Arrival       : %s\n", arrival);
        //TODO: Seat/Row kein Textfeld sondern ein Button der den Sitzplatz automatisch zuweist?
        g_print("Seat/Row      : %s\n", seat);
        g_print("---------------------------\n");

        createStructPerson();
        createListPersons();
        fillStructPerson(num, arrival, first_name, last_name);
//      fillStructPersonMan(ListPersons_t *list);

        addPerson(list, person);
        movePerson(list);
        freeListPersons(list);
        printListPersons(list);
        exportListPersons(list);

    } else {
        g_print("Error! Only 'Z' for Zivil or 'R' for Rettung is accepted.");
        exit(0);
    }

}


/* Reset input fields - delete */

static void entry_loeschen(gpointer evalu) {
    gint i;
    for(i=0; i<ENTRYS; i++)
        gtk_entry_set_text(entry[i], "");
}

int main(int argc, char **argv) {
    GtkWindow  *win;
    GdkPixbuf  *pic;
    GtkGrid    *table; //Pack widgets in rows and columns
    GtkLabel   *label[ENTRYS];
    GtkButton  *entry_button[3];
    GtkWidget  *hbox, *hbox_2, *hbox_3, *hbox_vscale; //Base class for all widgets
    GtkWidget  *vbox, *vbox_spin; //Base class for all widgets
    GtkWidget  *hsep;
    guint i;

    gtk_init( &argc, &argv );
    // Load a graphic into a pixbuf
    pic = gdk_pixbuf_new_from_file("icon/at-work.gif", NULL );
    // Create window with the following properties:
    win = g_object_new( GTK_TYPE_WINDOW,
                        "title", "Hospital Simulator",
                        "default-width",  380,
                        "default-height", 200,
                        "resizable", TRUE,
                        "window-position", GTK_WIN_POS_CENTER,
                        "border-width", 10,
                        "icon", pic,
                        NULL );
    // Create a table 8x3
    table = GTK_GRID(gtk_grid_new()); //Creates a new Grid-Widget
    gtk_grid_set_row_spacing(table, 3); //Sets the amount of space between rows of grid .
    gtk_grid_set_column_spacing(table, 3); //Sets the amount of space between columns of grid .
    // Create a horizontal box
    hbox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL , 10 ); //Creates a new GTK-Box -> GtkBox — A container for packing widgets in a single row or column
    // Create a second horizontal box
    hbox_2 = gtk_box_new( GTK_ORIENTATION_HORIZONTAL , 10 );


    // Create a vertical box
    vbox = gtk_box_new( GTK_ORIENTATION_VERTICAL , 10 );
    // Create a vertical box for the number fields
    vbox_spin = gtk_box_new( GTK_ORIENTATION_VERTICAL , 7 );

    // Creates ENTRYS number fields
    for(i=0; i < ENTRYS; i++) {
        entry[i] = GTK_ENTRY(gtk_entry_new());
        gtk_entry_set_text(entry[i], "Type here ...");
        gtk_entry_set_max_length(entry[i], BUF);
    }
    // Create labels for text fields
    label[0] = g_object_new( GTK_TYPE_LABEL,
                             "justify", GTK_JUSTIFY_LEFT,
                             "label", "First Name",
                             NULL );
    label[1] = g_object_new( GTK_TYPE_LABEL,
                             "justify", GTK_JUSTIFY_LEFT,
                             "label", "Last Name",
                             NULL );
    label[2] = g_object_new( GTK_TYPE_LABEL,
                             "label", "Arrival",
                             NULL );
    label[3] = g_object_new( GTK_TYPE_LABEL,
                             "label", "Seat/Row",
                             NULL );
    // Create buttons to evaluate the text fields
    entry_button[0] = g_object_new( GTK_TYPE_BUTTON, "label", "New Patient", NULL);
    entry_button[1] = g_object_new( GTK_TYPE_BUTTON,"label", "Reset",NULL );
    entry_button[2] = g_object_new( GTK_TYPE_BUTTON,"label", "Next Patient",NULL );


    // Create horizontal line
    hsep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);

    // Create Signalhandler for closing program
    g_signal_connect( win, "delete-event",
                      G_CALLBACK(delete_Event), NULL );
    g_signal_connect( win, "destroy",
                      G_CALLBACK(end), NULL );


    // Signalhandler for the Buttons
    g_signal_connect(entry_button[0], "clicked", G_CALLBACK(entry_evaluation), NULL);
    g_signal_connect( entry_button[1], "clicked",G_CALLBACK(entry_loeschen), NULL);
    g_signal_connect(entry_button[2], "clicked", G_CALLBACK(entry_evaluation), NULL);


/* Great packing of the widgets begins
*  Adds a widget to the grid.
*  The position of child is determined by left and top .
*  The number of “cells” that child will occupy is determined by width and height .
*/
    gtk_grid_attach ( table, GTK_WIDGET(label[0]),0, 0, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(entry[0]),1, 0, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(label[1]),0, 2, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(entry[1]),1, 2, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(label[2]),0, 3, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(entry[2]),1, 3, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(label[3]), 0, 4, 1, 1  );
    gtk_grid_attach ( table, GTK_WIDGET(entry[3]), 1, 4, 1, 1);

    gtk_grid_attach ( table, GTK_WIDGET(hbox),1, 6, 1, 1);

/* Adds child to box , packed with reference to the start of box .
*  The child is packed after any other child packed with reference to the start of box .
*/

    gtk_box_pack_start( GTK_BOX(hbox),GTK_WIDGET(entry_button[0]),FALSE, FALSE, 0); //New Button
    gtk_box_pack_start( GTK_BOX(hbox),GTK_WIDGET(entry_button[1]),FALSE, FALSE, 0); //Reset Button
    gtk_box_pack_start( GTK_BOX(hbox), GTK_WIDGET( entry_button[2]), FALSE, FALSE, 0); //Next Button

    gtk_box_pack_start( GTK_BOX(vbox_spin),GTK_WIDGET(hsep),FALSE, FALSE, 0);

/* Adds widget to container . Typically used for simple containers such as GtkWindow,
 * GtkFrame, or GtkButton; for more complicated layout containers such as GtkBox or GtkGrid,
 * this function will pick default packing parameters that may not be correct.
 *
*/

    gtk_container_add( GTK_CONTAINER( vbox ),GTK_WIDGET( hbox_2) );
    gtk_container_add( GTK_CONTAINER( hbox_2 ),GTK_WIDGET( table ) );
    gtk_container_add( GTK_CONTAINER( win ), GTK_WIDGET( vbox ) );

/* Show the window */
    gtk_widget_show_all( GTK_WIDGET(win) );

/* Mainloop of gtk. Program awaits interaction  */
    gtk_main();
    g_print("The Main loop has been terminated.\n");

    return 0;
}

/*
	// Possible example of Person-List-creation: ListPersons_t activePersons = createListPersons();
	// ^ Will be executed 2 times to generate an active Persons-List and an inactive Persons-List
	// Possible example of Row-List-creation: ListRows_t row1 = createListRow();
	// ^ Will be executed 5 times to generate 5 rows.

	// Testing my functions
	Person_t person_1 = {.num = 1, .arrival = 'Z', .first_name = "Christian", .last_name = "Griffith", .neighbour = {NULL, NULL}, .seat = NULL};
	Person_t person_2 = {.num = 2, .arrival = 'Z', .first_name = "Clara", .last_name = "Tate", .neighbour = {NULL, NULL}, .seat = NULL};
	Person_t person_3 = {.num = 3, .arrival = 'Z', .first_name = "Emily", .last_name = "Lane", .neighbour = {NULL, NULL}, .seat = NULL};
	Person_t person_4 = {.num = 4, .arrival = 'Z', .first_name = "Luis", .last_name = "Herrera", .neighbour = {NULL, NULL}, .seat = NULL};
	Person_t person_5 = {.num = 5, .arrival = 'Z', .first_name = "Callie", .last_name = "Moore", .neighbour = {NULL, NULL}, .seat = NULL};
	Person_t person_6 = {.num = 6, .arrival = 'Z', .first_name = "Mae", .last_name = "Richardson", .neighbour = {NULL, NULL}, .seat = NULL};
	Person_t person_7 = {.num = 7, .arrival = 'Z', .first_name = "Agnes", .last_name = "Underwood", .neighbour = {NULL, NULL}, .seat = NULL};
	Person_t person_8 = {.num = 8, .arrival = 'Z', .first_name = "Allie", .last_name = "Chapman", .neighbour = {NULL, NULL}, .seat = NULL};
	Person_t person_9 = {.num = 9, .arrival = 'Z', .first_name = "Garrett", .last_name = "Frazier", .neighbour = {NULL, NULL}, .seat = NULL};
	Person_t person_10 = {.num = 10, .arrival = 'Z', .first_name = "John", .last_name = "Silva", .neighbour = {NULL, NULL}, .seat = NULL};
	ListRows_t *row_1 = createRow();
	ListRows_t *row_2 = createRow();
	ListRows_t *row_3 = createRow();
	ListRows_t *row_4 = createRow();
	ListRows_t *row_5 = createRow();
	ListRows_t *rows[5] = {row_1, row_2, row_3, row_4, row_5};
	occupySeat(row_1, &person_1);
	occupySeat(row_2, &person_2);
	occupySeat(row_3, &person_3);
	occupySeat(row_2, &person_4);
	occupySeat(row_1, &person_5);
	occupySeat(row_4, &person_6);
	occupySeat(row_5, &person_7);
	occupySeat(row_1, &person_8);
	occupySeat(row_1, &person_9);
	selectRow(rows, &person_10);
	for (int i = 1; i <= MAX_ROWS; i++)
	{
		printf("---- Printing row %d ----\n", i);
		Seat_t *current = rows[i - 1]->start;
		while (current != NULL)
		{
			if (current->occupied != NULL)
			{
				printf("Name: %s %s\n", current->occupied->first_name, current->occupied->last_name);
			}
			else
			{
				printf("<NULL>\n");
			}
			current = current->node.next;
		}
	}

*/
