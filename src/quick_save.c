#include <stdio.h>
#include <stdlib.h>

#include "hospital_structures.h"
// #include "auto_serializer.h"
#include "serialize.h" // Custom Library from the Internet to serialize C-Structures (Credits/Sources in serialize.h)
#include "seat_rows.h"
#include "persons.h"

typedef struct hospital_translators
{
	ser_tra_t *t_node_p;
	// ser_tra_t *t_node_s;
	ser_tra_t *t_person;
	ser_tra_t *t_person_ref;
	// ser_tra_t *t_seat;
	// ser_tra_t *t_listPerson;
	// ser_tra_t *t_listRow;
} hospital_tra_t;

FILE *in;
FILE *out;

/* NOTE was used for "auto_serializer.h", didn't work out as intended
int write_fn(const uint8_t *bytes, size_t n, void *q)
{
	size_t written;
	if ((written = fwrite(bytes, sizeof(uint8_t), n, (FILE *)q)) == 0)
	{
		return 1;
	}
	else
	{
		printf("Wrote %zu bytes\n", written);
		return 0;
	}
	// fflush((FILE *)q);
}
int read_fn(uint8_t *bytes, size_t n, void *q)
{
	size_t read;
	if ((read = fread(bytes, sizeof(uint8_t), n, (FILE *)q)) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// Current strategy: DUMP everything in a matter of "I have no idea of what I'm doing and will improve results later"
void quick_save(ListPersons_t *active, ListPersons_t *completed, ListRows_t **rows)
{
	int a = 0xAA;
	int b = 0xBB;
	int c = 0xCC;
	if (active->start != NULL)
	{
		if (!cser_raw_store_struct_ListPersons(active, write_fn, out))
		{
			fprintf(stderr, "Serialization {persons_active} completed!\n");
		}
	}
	fwrite(&a, sizeof(uint8_t), 1, out);
	if (completed->start != NULL)
	{
		if (!cser_raw_store_struct_ListPersons(completed, write_fn, out))
		{
			fprintf(stderr, "Serialization {persons_completed} completed!\n");
		}
	}
	fwrite(&b, sizeof(uint8_t), 1, out);
	for (int i = 0; i < MAX_ROWS; i++)
	{
		if (rows[i] == NULL)
		{
			continue;
		}
		if (!cser_raw_store_struct_ListRows(rows[i], write_fn, out))
		{
			fprintf(stderr, "Serialization {rows[%d]} completed!\n", i);
		}
		fwrite(&c, sizeof(uint8_t), 1, out);
	}
}
*/

void quick_save(ListPersons_t *active, ListPersons_t *completed, ListRows_t **rows)
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
	/* NOTE All the stuff I won't serialize because it's freaking complicated (It's faulty)
	// translators->t_seat = ser_new_tra("seat", sizeof(Seat_t), NULL);
	// ser_new_field(translators->t_seat, "person_ref", 1, "occupied", offsetof(Seat_t, occupied));
	// translators->t_node_s = ser_new_tra("node_s", sizeof(struct node_s), translators->t_seat);
	// ser_new_field(translators->t_node_p, "seat", 1, "s_next", offsetof(struct node_s, next));
	// ser_new_field(translators->t_node_p, "seat", 1, "s_prev", offsetof(struct node_s, prev));
	// ser_new_field(translators->t_seat, "node_s", 0, "node_s", offsetof(Seat_t, node));
	// translators->t_listPerson = ser_new_tra("listPerson", sizeof(ListPersons_t), translators->t_person);
	// ser_new_field(translators->t_listPerson, "ushort", 0, "p_count", offsetof(ListPersons_t, count));
	// ser_new_field(translators->t_listPerson, "ushort", 0, "p_countZivil", offsetof(ListPersons_t, countZivil));
	// ser_new_field(translators->t_listPerson, "person_ref", 1, "p_start", offsetof(ListPersons_t, start));
	// ser_new_field(translators->t_listPerson, "person_ref", 1, "p_last", offsetof(ListPersons_t, last));
	// translators->t_listRow = ser_new_tra("listRow", sizeof(ListRows_t), translators->t_seat);
	// ser_new_field(translators->t_listRow, "ushort", 0, "s_count", offsetof(ListRows_t, count));
	// ser_new_field(translators->t_listPerson, "seat", 1, "s_start", offsetof(ListRows_t, start));
	// ser_new_field(translators->t_listPerson, "seat", 1, "s_last", offsetof(ListRows_t, last));
	// translators->t_neighbours = ser_new_tra("neighbours", sizeof(Person_t.neighbour), translators->t_person);
	// ser_new_field(translators->t_neighbours, "person_ref", 1, "neighbour", offsetof(Person_t, neighbour));

	// ser_new_field(translators->t_person, "node_p", 1, "node_p", offsetof(Person_t, node));
	// translators->t_listPerson = ser_new_tra("listPerson", sizeof(ListPersons_t), translators->t_person);
	// ser_new_field(translators->t_listPerson, "person", 1, "p_start", offsetof(ListPersons_t, start));
	// ser_new_field(translators->t_listPerson, "person", 1, "p_last", offsetof(ListPersons_t, last));

	// Translators for Seat-Stuff
	// translators.t_seat = ser_new_tra("seat", sizeof(Seat_t), NULL);
	// translators.t_node_s = ser_new_tra("node_s", sizeof(node_s), translators.t_seat);
	// translators.t_listRow = ser_new_tra("listRow", sizeof(ListRows_t), translators.t_seat);
	*/
	return translators;
}

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
