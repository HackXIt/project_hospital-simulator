#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#define VBOX   3
#define ENTRYS 3
#define SCALES 3
#define SPIN   2
#define BUF 50


static  GtkEntry   *entry[ENTRYS]; //    Textfelder - GtkEntry
static gint;


delete_Event(GtkWidget *widget, GdkEvent event, gpointer daten) {
    g_print("Die Anwendung wird beendet.\n");
    /* Nur mit FALSE wird die Anwendung wirklich Beendet */
    return FALSE;
}

static void end ( GtkWidget *widget, gpointer daten ) {
    g_print("Good Bye!\n");
    gtk_main_quit();
}

/* Auswertung Eingabefelder */
static void entry_auswerten(gpointer auswert) {
    gchar *e1, *e2, *e3;
    g_object_get(entry[0], "text", &e1, NULL);
    g_object_get(entry[1], "text", &e2, NULL);
    g_object_get(entry[2], "text", &e3, NULL);
    g_print("Entry-Feld Auswertung:\n");
    g_print("New Patient   : %s\n", e1);
    g_print("Arrival : %s\n", e2);
    g_print("Seat/Row         : %s\n", e3);
    g_print("---------------------------\n");
}



/* Eingabefelder zurücksetzen - löschen */
static void entry_loeschen(gpointer auswert) {
    gint i;
    for(i=0; i<ENTRYS; i++)
        gtk_entry_set_text(entry[i], "");
}

int main(int argc, char **argv) {
    GtkWindow  *win;
    GdkPixbuf  *pic;
    GtkGrid    *table; //Pack widgets in rows and columns
    GtkLabel   *label[ENTRYS];
    GtkButton  *entry_button[2];
    GtkWidget  *hbox, *hbox_2, *hbox_3, *hbox_vscale; //Base class for all widgets
    GtkWidget  *vbox, *vbox_spin; //Base class for all widgets
    GtkWidget  *hsep;
    guint i;

    gtk_init( &argc, &argv );
    /* Eine Grafik in einen Pixbuf laden */
    pic = gdk_pixbuf_new_from_file("icon/at-work.gif", NULL );
    /* Fenster mit folgenden Eigenschaften anlegen */
    win = g_object_new( GTK_TYPE_WINDOW,
                        "title", "Hospital Simulator",
                        "default-width",  380,
                        "default-height", 200,
                        "resizable", TRUE,
                        "window-position", GTK_WIN_POS_CENTER,
                        "border-width", 10,
                        "icon", pic,
                        NULL );
    /* Eine Tabelle 8x3 erzeugen */
    table = GTK_GRID(gtk_grid_new()); //Erzeugt ein neues Grid-Widget(Gitter)
    gtk_grid_set_row_spacing(table, 3); //Sets the amount of space between rows of grid .
    gtk_grid_set_column_spacing(table, 3); //Sets the amount of space between columns of grid .
    /* horizontale Box erzeugen */
    hbox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL , 10 ); //Creates a new GTK-Box -> GtkBox — A container for packing widgets in a single row or column
    /* horizontale Box erzeugen */
    hbox_2 = gtk_box_new( GTK_ORIENTATION_HORIZONTAL , 10 ); //A container for packing widgets (Vorrichtungen) in a single row or column

    //   hbox_3 = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 10); //<

    /* vertikale Box erzeugen */
    vbox = gtk_box_new( GTK_ORIENTATION_VERTICAL , 10 );
    /* vertiakle Box für Zahlenfelder erzeugen */
    vbox_spin = gtk_box_new( GTK_ORIENTATION_VERTICAL , 7 );

    /* ENTRYS Textfelder erzeugen */
    for(i=0; i < ENTRYS; i++) {
        entry[i] = GTK_ENTRY(gtk_entry_new());
        gtk_entry_set_text(entry[i], "Type here ...");
        gtk_entry_set_max_length(entry[i], BUF);
    }
    /* Labels für die Textfelder erzeugen */
    label[0] = g_object_new( GTK_TYPE_LABEL,
                             "justify", GTK_JUSTIFY_LEFT,
                             "label", "Name",
                             NULL );
    label[1] = g_object_new( GTK_TYPE_LABEL,
                             "label", "Arrival",
                             NULL );
    label[2] = g_object_new( GTK_TYPE_LABEL,
                             "label", "Seat/Row",
                             NULL );
    /* Buttons zum Auswerten der Textfelder erzeugen */
    entry_button[0] = g_object_new( GTK_TYPE_BUTTON,"label", "New Patient",NULL );
    entry_button[1] = g_object_new( GTK_TYPE_BUTTON,"label", "Reset",NULL );
 // entry_button[2] = g_object_new( GTK_TYPE_BUTTON,  "label", "Next Patient", NULL);

    // horizontale Linie erzeugen
    hsep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    // Signalhandler einrichten
    g_signal_connect( win, "delete-event",
                      G_CALLBACK(delete_Event), NULL );
    g_signal_connect( win, "destroy",
                      G_CALLBACK(end), NULL );
    // Signalhandler für die Buttons
    g_signal_connect( entry_button[0], "clicked",G_CALLBACK(entry_auswerten), NULL);
    //  g_signal_connect( entry_button[2], "clicked",G_CALLBACK(entry_auswerten, NULL );
    g_signal_connect( entry_button[1], "clicked",G_CALLBACK(entry_loeschen), NULL);

/* Großes Packen der Widget beginnt */
/*Adds a widget to the grid.
The position of child is determined by left and top .
The number of “cells” that child will occupy is determined by width and height . */
    gtk_grid_attach ( table, GTK_WIDGET(label[0]),0, 0, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(entry[0]),1, 0, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(label[1]),0, 2, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(entry[1]),1, 2, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(label[2]),0, 4, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(entry[2]),1, 4, 1, 1);
    gtk_grid_attach ( table, GTK_WIDGET(hbox),1, 6, 1, 1);
/*Adds child to box , packed with reference to the start of box .
The child is packed after any other child packed with reference to the start of box .*/

    gtk_box_pack_start( GTK_BOX(hbox),GTK_WIDGET(entry_button[0]),FALSE, FALSE, 0); //New
    gtk_box_pack_start( GTK_BOX(hbox),GTK_WIDGET(entry_button[1]),FALSE, FALSE, 0); //Reset

   //   gtk_box_pack_start( GTK_BOX(hbox_2), GTK_WIDGET(entry_button[2]), FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(vbox_spin),GTK_WIDGET(hsep),FALSE, FALSE, 0);

/*Adds widget to container . Typically used for simple containers such as GtkWindow,
 * GtkFrame, or GtkButton; for more complicated layout containers such as GtkBox or GtkGrid,
 * this function will pick default packing parameters that may not be correct. */

    gtk_container_add( GTK_CONTAINER( vbox ),GTK_WIDGET( hbox_2) );
    gtk_container_add( GTK_CONTAINER( hbox_2 ),GTK_WIDGET( table ) );
  //  gtk_container_add( GTK_CONTAINER( hbox_2 ),GTK_WIDGET( hbox_vscale ) );
    gtk_container_add( GTK_CONTAINER( win ), GTK_WIDGET( vbox ) );

    /* Fenster anzeigen */
    gtk_widget_show_all( GTK_WIDGET(win) );

    /* Hauptschleife von gtk */
    gtk_main();
    g_print("Die GTK-Hauptschleife wurde beendet\n");
    return 0;
}



















