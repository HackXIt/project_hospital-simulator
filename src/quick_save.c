#include <stdio.h>
#include <stdlib.h>

#include "hospital_structures.h"
#include "seat_rows.h"
#include "persons.h"

FILE *tmp_file = NULL;

// Current strategy: DUMP everything in a matter of "I have no idea of what I'm doing and will improve results later"
void quick_save(ListPersons_t *active, ListPersons_t *completed, ListRows_t **rows)
{
	fwrite(active, sizeof(ListPersons_t *), 1, tmp_file);
	Person_t *tmp = active->start;
	while (tmp != NULL)
	{
		fwrite(tmp, sizeof(Person_t *), 1, tmp_file);
		if (tmp->seat != NULL)
		{
			fwrite(tmp->seat, sizeof(Seat_t *), 1, tmp_file);
		}
		tmp = tmp->node.next;
	}
	fwrite(completed, sizeof(ListPersons_t *), 1, tmp_file);
	tmp = completed->start;
	while (tmp != NULL)
	{
		fwrite(tmp, sizeof(Person_t *), 1, tmp_file);
		tmp = tmp->node.next;
	}
	fwrite(rows, sizeof(ListRows_t **), 1, tmp_file);
	for (int i = 0; i < MAX_ROWS; i++)
	{
		if (rows[i] == NULL)
		{
			continue;
		}
		fwrite(rows[i], sizeof(ListRows_t *), 1, tmp_file);
	}
	fflush(tmp_file);
}

int main(int argc, char const *argv[])
{
	tmp_file = fopen("test.dat", "wb");
	ListPersons_t *p_active = createListPersons();
	ListPersons_t *p_completed = createListPersons();
	ListRows_t *row_1 = createRow();
	ListRows_t *row_2 = createRow();
	ListRows_t *rows[5] = {row_1, row_2, NULL, NULL, NULL};
	Person_t *p1 = fillStructPerson('Z', "Wesley", "Ortega");
	Person_t *p2 = fillStructPerson('Z', "Lewis", "McBride");
	Person_t *p3 = fillStructPerson('Z', "Rachel", "Jimenez");
	Person_t *p4 = fillStructPerson('R', "Bertie", "Porter");
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

	printListPersons(p_completed);
	exportListPersons(p_completed);

	fflush(tmp_file);
	fclose(tmp_file);

	return 0;
}
