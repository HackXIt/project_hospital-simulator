/*--- COMMON LIBRARIES ---*/
#include <stdio.h>
#include <stdlib.h>
/*--- CUSTOM LIBRARIES ---*/
#include "hospital_structures.h"
#include "seat_rows.h"
/*--- MACROS ---*/
#define MAX_ROWS 5
#define MAX_SEATS 5

// Create Seat
Seat_t *createSeat()
{
	Seat_t *newSeat = calloc(1, sizeof(Seat_t));
	if (newSeat == NULL)
	{
		// TODO Memory-Error-Handling in createSeat();
		return NULL;
	}
	return newSeat;
}

// Create Sitzreihe - Nick
ListRows_t *createRow()
{
	ListRows_t *newRow = calloc(1, sizeof(ListRows_t)); // Initializes values with
	if (newRow == NULL)
	{
		// TODO Memory-Error-Handling in createRow();
		return NULL;
	}
	newRow->count = 0;
	newRow->start = createSeat();
	newRow->last = newRow->start;
	for (int i = 0; i < MAX_SEATS - 1; i++)
	{
		Seat_t *newSeat = createSeat();
		newRow->last->node.next = newSeat;
		newSeat->node.prev = newRow->last;
		newRow->last = newSeat;
	}
	return newRow;
}

// Occupy a seat in the row with the given person
int occupySeat(ListRows_t *row, Person_t *person)
{
	Seat_t *current = row->start;
	// Checking if the row is full must be done before occupying, otherwise there will be SEG_FAULT
	while (current->occupied != NULL)
	{
		current = current->node.next;
	}
	// TODO Create logic where an empty seat between persons is preferred, if possible at all
	// Current logic is "First come, first served"
	if (current->occupied == NULL)
	{
		current->occupied = person;
		person->seat = current;
		row->count++;
		return EXIT_SUCCESS;
	}
	// NOTE This can never be reached, because if the row is fully occupied, it causes a SEG_FAULT
	return EXIT_FAILURE;
}

// Assign Person to seat - Nick
// int assignSeat(ListRows_t *row, Person_t *person)
// {
//     if (row->count < 5)
//     {
//         Seat_t *temp = occupySeat(person);
//         if (temp == NULL)
//         {
//             fprintf(stderr, "Couldn't occupy seat.");
//             return EXIT_FAILURE;
//         }
//         row->last->node.next = temp;
//         temp->node.prev = row->last;
//         row->last = temp;
//         return EXIT_SUCCESS;
//     }
//     return EXIT_FAILURE;
// }

//Select Sitzreihe (Auswahl des freien Platzes) - Nick
// Select the row with the lowest person count and occupy a seat in that row
int selectRow(ListRows_t *rows[MAX_ROWS], Person_t *person)
{
	ListRows_t *selection = NULL;
	int lowest = MAX_SEATS;
	for (int i = 0; i < MAX_ROWS; i++)
	{
		if (lowest > rows[i]->count)
		{
			selection = rows[i];
			lowest = rows[i]->count;
		}
	}
	if (selection != NULL)
	{
		occupySeat(selection, person);
		return EXIT_SUCCESS;
	}
	// TODO Error-Message when all rows are full
	return EXIT_FAILURE;
}

// Free the whole row from memory - Nick
int freeRow(ListRows_t *row)
{
	Seat_t *current = row->start; // Temporarily save current node
	while (current != NULL)
	{
		row->start = current->node.next; // move head of list to next node
		free(current);					 // free current node
		current = row->start;			 // move current node to head
	}
	free(row); // free list head
	return EXIT_SUCCESS;
}

/*
// Free a single seat in the list
int freeSeat(Seat_t *seat)
{
	Seat_t *temp = seat->node.prev;				  // Temporarily save previous seat
	seat->node.prev->node.next = seat->node.next; // Link previous seat with next seat
	seat->node.next->node.prev = temp;			  // Link next seat with the previous, using the temporary pointer
	free(seat);									  // Free the now unlinked seat
	return EXIT_SUCCESS;
}
 */