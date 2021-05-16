#include <stdio.h>
#include <stdlib.h>
#include "gtk3.h"
#include "hospital_structures.h"
#include "persons.h"
#include "seat_rows.h"

#define ENTRYS 4

//Global Variables:
extern GtkEntry   *entry[ENTRYS]; //Textfields GtkEntry



gint delete_Event(GtkWidget *widget, GdkEvent event, gpointer data) {
    g_print("Die Anwendung wird beendet.\n");
    // Only with FALSE the application is really terminated
    return FALSE;
}

 void end ( GtkWidget *widget, gpointer data ) {
    g_print("Good Bye!\n");
    gtk_main_quit();
}

/* Evaluation input fields */
void entry_evaluation(gpointer eval) {
    gchar *first_name, *last_name, *seat;
    unsigned short num = 0;
    char arrival;
    ListPersons_t *list;
    Person_t *person = NULL;
    
    g_object_get(entry[0], "text", &first_name, NULL);
    g_object_get(entry[1], "text", &last_name, NULL);
    g_object_get(entry[2], "text", &arrival, NULL);
    g_object_get( entry[3], "text", &seat, NULL);
    g_print("Entry-Field Evaluation:\n");
    //TODO: Statt New Patient, Vorname, Nachname in jeweils eine Zeile. Check!
    g_print("First Name   : %s\n", first_name);
    g_print( "Last Name   : %s\n", last_name);
    //TODO: MainTask: Es darf nur "Z" oder "R" angenommen werden. Sonst Fehlermeldung. Check!
    //TODO: Optional: Arrival Button wird aufgerufen und entweder "Z" oder "R" anklicken. Checkboxen vllt
    if((arrival == 'Z') || (arrival == 'R')){
        g_print("Arrival       : %c\n", arrival);

        createStructPerson();
        createListPersons();
        fillStructPerson(num, arrival, first_name,last_name);
//      fillStructPersonMan(ListPersons_t *list);

        addPerson(list, person);
        movePerson(list);
        freeListPersons(list);
        printListPersons(list);
        exportListPersons(list);

    }else{
        g_print("Error! Only 'Z' for Zivil or 'R' for Rettung is accepted.");
        exit(0);
    }


    //TODO: Nick fragen: Seat/Row kein Textfeld sondern ein Button der den Sitzplatz automatisch zuweist?
    g_print("Seat/Row      : %s\n", seat);
    g_print("---------------------------\n");
}

/* Reset input fields - delete */
void entry_loeschen(gpointer eval) {
    gint i;
    for(i=0; i<ENTRYS; i++)
        gtk_entry_set_text(entry[i], "");
}

















