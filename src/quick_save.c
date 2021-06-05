#include <stdio.h>
#include <stdlib.h>

#include "hospital_structures.h"
#include "serialize.h" // Custom Library from the Internet to serialize C-Structures (Credits/Sources in serialize.h)
#include "seat_rows.h"
#include "persons.h"
#include "quick_save.h"

void quick_save(ListPersons_t *active, ListPersons_t *completed)
{
	return;
}

hospital_tra_t *initialize_translators()
{
	hospital_tra_t *translators = calloc(1, sizeof(hospital_tra_t));
	// Translators for Person-Stuff
	translators->t_person = ser_new_tra("person", sizeof(Person_t), NULL);
	ser_new_field(translators->t_person, "char", 0, "arrival", offsetof(Person_t, arrival));
	ser_new_field(translators->t_person, "string", 0, "first_name", offsetof(Person_t, first_name));
	ser_new_field(translators->t_person, "string", 0, "last_name", offsetof(Person_t, last_name));
	translators->t_node_p = ser_new_tra("node_p", sizeof(struct node_p), translators->t_person);
	ser_new_field(translators->t_node_p, "person", 1, "p_next", offsetof(struct node_p, next));
	ser_new_field(translators->t_node_p, "person", 1, "p_prev", offsetof(struct node_p, prev));
	ser_new_field(translators->t_person, "node_p", 0, "node_p", offsetof(Person_t, node));
	translators->t_person_ref = ser_new_tra("person_ref", sizeof(Person_t), translators->t_person);
	ser_new_field(translators->t_person_ref, "string", 0, "first_name", offsetof(Person_t, first_name));
	ser_new_field(translators->t_person_ref, "string", 0, "last_name", offsetof(Person_t, last_name));
	ser_new_field(translators->t_person, "person_ref", 1, "left_neighbour", offsetof(Person_t, neighbour[0]));
	ser_new_field(translators->t_person, "person_ref", 1, "right_neighbour", offsetof(Person_t, neighbour[1]));
	return translators;
}

/* NOTE This main is for testing-purposes of quick_save.c and can be compiled using `make quicksave`
int main(int argc, char const *argv[])
{
	hospital_tra_t *trans = initialize_translators();
	out = fopen("test.tmp", "w");
	char *output;
	ListPersons_t *p_active = createListPersons();
	ListPersons_t *p_completed = createListPersons();
	ListRows_t *row_1 = createRow();
	ListRows_t *row_2 = createRow();
	// ListRows_t *row_3 = createRow();
	ListRows_t *rows[5] = {row_1, row_2, NULL, NULL, NULL};
	Person_t *p1 = fillStructPerson('Z', "Wesley", "Ortega");
	Person_t *p2 = fillStructPerson('Z', "Lewis", "McBride");
	Person_t *p3 = fillStructPerson('Z', "Rachel", "Jimenez");
	Person_t *p4 = fillStructPerson('Z', "Joshua", "Allen");
	Person_t *p5 = fillStructPerson('Z', "Bertie", "Guerrero");
	Person_t *p6 = fillStructPerson('Z', "Dennis", "McDonald");
	Person_t *p7 = fillStructPerson('Z', "Daisy", "Manning");
	Person_t *p8 = fillStructPerson('Z', "Herman", "Patterson");
	Person_t *p9 = fillStructPerson('Z', "Rodney", "Fletcher");
	Person_t *p10 = fillStructPerson('Z', "Christine", "Harper");
	Person_t *p11 = fillStructPerson('R', "Bess", "Dixon");
	Person_t *p12 = fillStructPerson('R', "Rachel", "Hampton");

	// Filling hospital
	addPerson(p_active, p1);
	selectRow(rows, p1);
	addPerson(p_active, p2);
	selectRow(rows, p2);
	addPerson(p_active, p3);
	selectRow(rows, p3);
	addPerson(p_active, p4);
	selectRow(rows, p4);
	addPerson(p_active, p5);
	selectRow(rows, p5);
	addPerson(p_active, p6);
	selectRow(rows, p6);
	addPerson(p_active, p7);
	selectRow(rows, p7);
	addPerson(p_active, p8);
	selectRow(rows, p8);
	addPerson(p_active, p9);
	selectRow(rows, p9);
	addPerson(p_active, p10);
	selectRow(rows, p10);
	addPerson(p_active, p11);
	selectRow(rows, p11);
	addPerson(p_active, p12);
	selectRow(rows, p12);
	// quick_save(p_active, p_completed, rows);
	// output = ser_ialize(trans->t_person, "person", p_active->start, NULL, 0);
	output = ser_ialize(trans->t_person, "person", p_active->start, NULL, 0);
	fprintf(out, "Result:\n%s\n", output);
	printf("Result:\n%s\n", output);
	free(output);
	// fflush(out);
	// fclose(out);
	printListPersons(p_active);

	// out = fopen("test2.dat", "wb");

	printf("\n\n----BREAK----\n\n");

	// Emptying Hospital
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	movePerson(p_active, p_completed);
	clearSeat(p_completed->last);
	// quick_save(p_active, p_completed, rows);
	output = ser_ialize(trans->t_person, "person", p_completed->start, NULL, 0);
	printf("Result:\n%s\n", output);
	free(output);
	printListPersons(p_completed);
	// exportListPersons(p_completed);

	// fflush(out);
	// fclose(out);

	freeListPersons(p_active);
	freeListPersons(p_completed);
	for (int i = 0; i < MAX_ROWS; i++)
	{
		if (rows[i] == NULL)
		{
			continue;
		}
		freeRow(rows[i]);
	}

	ser_del_tra(trans->t_person);
	free(trans);
	return 0;
}
*/