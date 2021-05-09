/* MAIN.c
 *   by Nikolaus Rieder, Stefan Bittgen, Eva Grabler
 * Description:
 *   Main execution of the project
**/

/*--- COMMON LIBRARIES ---*/
#include <stdio.h>
#include <stdlib.h>
/*--- CUSTOM LIBRARIES ---*/
#include "hospital_structures.h"
#include "seat_rows.h"
/*--- MACROS ---*/

int main()
{

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
	return 0;
}