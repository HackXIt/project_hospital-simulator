#include <stdlib.h>	  // For macro's and other relevant C-things
#include <gtk/gtk.h>  // All the GTK-Stuff I guess
#include <gtk/gtkx.h> // Don't know
#include <string.h>	  // All the string stuff

// Global pointers for widgets
GtkBuilder *builder;				 // For the builder object, which dynamically links the XML to the code
GtkWidget *main_window;				 // For the main window - GtkWindow
GtkWidget *window_sections;			 // For the initial window grid - GtkGrid
GtkWidget *col1_pane1;				 // 1st Column, 1st Pane - GtkPaned
GtkWidget *pane1_top;				 // 1st Pane, top-part, fixed Container - GtkFixed
GtkWidget *button_addPatient;		 // Button for adding a Patient - GtkButton
GtkWidget *button_nextPatient;		 // Button for checking next patient - GtkButton
GtkWidget *pane1_bottom;			 // 1st Pane, bottom-part, expandable Container - GtkExpander
GtkWidget *expander_patient_info;	 // Label for expandable Container 'pane1_bottom' - GtkLabel
GtkWidget *patient_info;			 // fixed Container for patient information filled or unfilled - GtkFixed
GtkWidget *label_patient_name;		 // Label for the patient name entry - GtkLabel
GtkWidget *entry_patient_name;		 // Entry-Box for the patient name - GtkEntry
GtkWidget *label_patient_arrival;	 // Label for the patient arrival box - GtkLabel
GtkWidget *combobox_patient_arrival; // Combo-Box for the patient arrival - GtkComboBoxText

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file("hospital-simulator.glade");

	main_window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));				   // connect the glade-ID with the actual window widget
	g_signal_connect(GTK_WINDOW(main_window), "destroy", G_CALLBACK(gtk_main_quit), NULL); // gtk_main_quit() is called when Window is closed

	gtk_builder_connect_signals(builder, NULL); // Creates a dynamically linked table for all the signals in the glade-project with the code

	window_sections = GTK_WIDGET(gtk_builder_get_object(builder, "window_sections"));
	col1_pane1 = GTK_WIDGET(gtk_builder_get_object(builder, "col1_pane1"));
	pane1_top = GTK_WIDGET(gtk_builder_get_object(builder, "pane1_top"));
	button_addPatient = GTK_WIDGET(gtk_builder_get_object(builder, "button_addPatient"));
	button_nextPatient = GTK_WIDGET(gtk_builder_get_object(builder, "button_nextPatient"));
	pane1_bottom = GTK_WIDGET(gtk_builder_get_object(builder, "pane1_bottom"));
	expander_patient_info = GTK_WIDGET(gtk_builder_get_object(builder, "expander_patient_info"));
	patient_info = GTK_WIDGET(gtk_builder_get_object(builder, "patient_info"));
	label_patient_name = GTK_WIDGET(gtk_builder_get_object(builder, "label_patient_name"));
	entry_patient_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry_patient_name"));
	label_patient_arrival = GTK_WIDGET(gtk_builder_get_object(builder, "label_patient_arrival"));
	combobox_patient_arrival = GTK_WIDGET(gtk_builder_get_object(builder, "combobox_patient_arrival"));

	gtk_widget_show(main_window);

	gtk_main();

	return EXIT_SUCCESS;
}

void on_button_addPatient_clicked(GtkButton *button)
{
	gtk_expander_set_expanded(GTK_EXPANDER(expander_patient_info), TRUE);
}
