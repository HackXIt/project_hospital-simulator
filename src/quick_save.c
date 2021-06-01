#include <stdio.h>
#include <stdlib.h>

#include "hospital_structures.h"
// #include "auto_serializer.h"
#include "seat_rows.h"
#include "persons.h"

FILE *in;
FILE *out;

int a = 0xAA;
int b = 0xBB;
int c = 0xCC;

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

int main(int argc, char const *argv[])
{
	out = fopen("test.dat", "wb");
	ListPersons_t *p_active = createListPersons();
	ListPersons_t *p_completed = createListPersons();
	ListRows_t *row_1 = createRow();
	ListRows_t *rows[5] = {row_1, NULL, NULL, NULL, NULL};
	Person_t *p1 = fillStructPerson('Z', "Wesley", "Ortega");
	Person_t *p2 = fillStructPerson('Z', "Lewis", "McBride");
	Person_t *p3 = fillStructPerson('Z', "Rachel", "Jimenez");
	Person_t *p4 = fillStructPerson('R', "Ian", "Washington");
	Person_t *p5 = fillStructPerson('R', "Bertie", "Guerrero");
	Person_t *p6 = fillStructPerson('R', "Dennis", "McDonald");

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
	quick_save(p_active, p_completed, rows);
	fflush(out);
	fclose(out);

	out = fopen("test2.dat", "wb");

	printf("\nBREAK\n");

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
	quick_save(p_active, p_completed, rows);

	exportListPersons(p_completed);

	fflush(out);
	fclose(out);

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

	return 0;
}
