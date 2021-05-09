/*--- COMMON LIBRARIES ---*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--- CUSTOM LIBRARIES ---*/
#include "hospital_structures.h"
#include "persons.h"

/*--- MACROS ---*/

// Create empty struct of person
Person_t *createStructPerson() {
	Person_t *newStructPerson = calloc(1, sizeof(Person_t));
	if (newStructPerson == NULL) {
		fprintf(stderr, "Error while creating struct person.\n");
		return NULL;
	}
	return newStructPerson;
}

// Create list of persons
ListPersons_t *createListPersons() {
	ListPersons_t *newList = calloc(1, sizeof(ListPersons_t)); // initialized with 0
	if (newList == NULL) {
		fprintf(stderr, "Error while creating list of persons.\n");
		return NULL;
	}
	newList->count = 0;
	newList->start = NULL; // create first element and set it as start of list
	newList->last = NULL; // set first element also as last of list

	printf("Success: Creating list of persons.\n");
	return newList;
}

// Fill empty struct of person with given information
Person_t * fillStructPerson(unsigned short num, char arrival, char *first_name, char *last_name) {

	// create empty struct
	Person_t * newPerson = createStructPerson();

	// set num
	newPerson->num = num;

	// set arrival
	newPerson->arrival = arrival;

	// set first name
	newPerson->first_name = malloc(sizeof(char) * (strlen(first_name)+1));
	if (newPerson->first_name == NULL) {
		free(newPerson);
		return NULL;
	}
	strcpy(newPerson->first_name, first_name);

	// set last name
	newPerson->last_name = malloc(sizeof(char) * (strlen(last_name)+1));
	if (newPerson->last_name == NULL) {
		free(newPerson->first_name);
		free(newPerson);
		return NULL;
	}
	strcpy(newPerson->last_name, last_name);

	return newPerson;
}

// Insert person into list of persons according to mode of arrival
int addPerson(ListPersons_t *list, Person_t *person) {

	Person_t *newPerson = person;

    // if list is empty: insert new person (can be either type R or Z)
	if (list->start == NULL) { // we are at start, first element
		list->start = newPerson; // assign pointer to new start

	// if list ist not empty: find place for insertion depending on mode of arrival R or Z
	} else {

		Person_t *tmp = list->start; // tmp = pointer to start

		if (newPerson->arrival == 'R') { //	person of type R
			// case 1: insert before first Z - only Zs in list!
			if (tmp->arrival == 'Z'){
				tmp->node.prev = newPerson;
				newPerson->node.next = tmp;
				list->start = newPerson; // assign pointer to new start
			// case 2: insert after last R befort first Z
			} else {
				while (tmp->arrival == 'R') { // find last element of type  R
					tmp = tmp->node.next; //
				}

				Person_t *tmp1 = tmp->node.prev; // tmp1 = previous element (BEFORE place of insertion)
				Person_t *tmp2 = tmp; // tmp2 = following element (AFTER place of insertion)

				newPerson->node.prev = tmp1; // link between newPerson and previous element tmp1 - established in newPerson
				newPerson->node.next = tmp2; // link between newPerson and following element tmp2 - established in newPerson
				tmp1->node.next = newPerson; // link between newPerson and previous element tmp1 - established in previous element
				tmp2->node.prev = newPerson; // link between newPerson and following element tmp2 - established in following element
			}
		} else if (newPerson->arrival == 'Z') { // person of type Z
			// insert at end of list
			while (tmp->node.next != NULL) { // find last element tmp at end of list
				tmp = tmp->node.next;
			}

			tmp->node.next = newPerson; // set newPerson als new last element
			newPerson->node.prev = tmp; // set tmp as previous element of newPerson
		}
	}
	return 0;
}

// Move person from list
// TODO needs to be implemented

// Free list of persons
void freeListPersons(ListPersons_t *list){

	Person_t *tmp = list->start;
	while (tmp->node.next != NULL) { // until finding last element tmp at end of list
    	Person_t *next = tmp->node.next; // set pointer to next element in list after tmp
    	free(tmp->first_name);
        free(tmp->last_name);
        free(tmp);
        tmp = next; // set previously safed element next as new tmp
    }
    printf("Success: Freeing list of persons.\n");
}

// Print list of persons
void printListPersons(ListPersons_t *list){
	Person_t *tmp = list->start;
    while (tmp != NULL) { // until end of list
        printf("Number: %d\tArrival: %c\tFirst name: %s\tLast name: %s\n", tmp->num, tmp->arrival, tmp->first_name, tmp->last_name);
        tmp = tmp->node.next; // set next element as tmp
    }
    printf("\n");
}

// Export Persons
// TODO needs to be implemented
