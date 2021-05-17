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
#include "hospital_structures.h"
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

static void end(GtkWidget *widget, gpointer data)
{
	g_print("Good Bye!\n");
	gtk_main_quit();
}

/* Evaluation input fields */
static void entry_evaluation(gpointer evalu) {
    gchar *first_name, *last_name, *arrival; //, *seat;
    unsigned short num;
    ListPersons_t *list;
    Person_t *person;

    g_object_get(entry[0], "text", &first_name, NULL);
    g_object_get(entry[1], "text", &last_name, NULL);
 //   g_object_get(entry[2], "text", &arrival, NULL);
//    g_object_get(entry[3], "text", &seat, NULL);
    g_print("Entry-Field Evaluation:\n");
    g_print("First Name   : %s\n", first_name);
    g_print("Last Name   : %s\n", last_name);

//TODO: Arrival Button wird aufgerufen und entweder "Z" oder "R" anklicken. Checkboxen vllt
    if (strcmp(arrival, "Z") == 0 || strcmp(arrival, "R") == 0) {
  //      g_print("Arrival       : %s\n", arrival);
//TODO: Seat/Row kein Textfeld sondern soll durch den Button NEw Patient angestoßen werdne.
//      g_print("Seat/Row      : %s\n", seat);
        g_print("---------------------------\n");
/*
        fillStructPerson(num, arrival, first_name, last_name);
//      fillStructPersonMan(ListPersons_t *list);

        addPerson(list, person);
        movePerson(list);
        freeListPersons(list);
        printListPersons(list);
        exportListPersons(list);
*/
    } else {
        g_print("Error! Only 'Z' for Zivil or 'R' for Rettung is accepted.");
        exit(0);
    }
}

static void entry_loeschen(gpointer evalu) {
    gint i;
    for(i=0; i<ENTRYS-2; i++)
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
    gchar buf[BUF];

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
    for(i=0; i < ENTRYS-2; i++) {
        entry[i] = GTK_ENTRY(gtk_entry_new());
        gtk_entry_set_text(entry[i], "Type here ...");
        gtk_entry_set_max_length(entry[i], BUF);
    }


   // Our check button "Zivil"
    g_snprintf(buf, BUF, "Zivil");
    entry[2] = g_object_new( GTK_TYPE_CHECK_BUTTON, "label", buf, NULL);

    //Check button "Rettung"
    g_snprintf(buf, BUF, "Rettung");
    entry[3] = g_object_new( GTK_TYPE_CHECK_BUTTON, "label", buf, NULL);


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

    gtk_grid_attach ( table, GTK_WIDGET(entry[3]), 1, 4, 1, 1);

  gtk_grid_attach ( table, GTK_WIDGET(hbox),1, 6, 1, 1);

/* Adds child to box , packed with reference to the start of box .
*  The child is packed after any other child packed with reference to the start of box .
*/
    gtk_box_pack_start( GTK_BOX(hbox),GTK_WIDGET(entry_button[0]),FALSE, FALSE, 0); //New Button
    gtk_box_pack_start( GTK_BOX(hbox),GTK_WIDGET(entry_button[1]),FALSE, FALSE, 0); //Reset Button
    gtk_box_pack_start( GTK_BOX(hbox), GTK_WIDGET( entry_button[2]), FALSE, FALSE, 0); //Next Button

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
    gtk_widget_show_all( GTK_WIDGET(win) );

/* Mainloop of gtk. Program awaits interaction  */
    gtk_main();
    g_print("The Main loop has been terminated.\n");

	return 0;
}
