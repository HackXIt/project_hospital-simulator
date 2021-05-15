/*--- COMMON LIBRARIES ---*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--- CUSTOM LIBRARIES ---*/
#include "hospital_structures.h"
#include "persons.h"

/*--- MACROS ---*/
#define MAXLENGTH_NAME 20

// TODO Error handling in this file

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

	/*
	newPerson->neighbour[0] = NULL; // TODO Ask colleagues is this necessary?
    newPerson->neighbour[1] = NULL;
*/
	return newPerson;
}

// TODO implement function - is this even necessary?
// Fill empty struct of person with information provided by user input
/*
Person_t * fillStructPersonMan(ListPersons_t *list){
    // create empty struct
    Person_t * newPerson = createStructPerson();

    // set num
    newPerson->num = list->count + 1;

    // set arrival
    char c;
    char buf[2];
    printf("Insert Type of arrival: ");
    do {scanf("%c",&c);} while ( getchar() != '\n' );
    newPerson->arrival = c;

    // set first name
    char firstName [MAXLENGTH_NAME];
    printf("Insert first name: ");
    scanf("%s", firstName);
    newPerson->first_name = malloc(sizeof(char) * (MAXLENGTH_NAME+1));
    if (newPerson->first_name == NULL) {
        free(newPerson);
        return NULL;
    }
    strcpy(newPerson->first_name, firstName);

    // set last name
    char lastName [MAXLENGTH_NAME];
    printf("Insert last name: ");
    scanf("%s", lastName);
    newPerson->last_name = malloc(sizeof(char) * (MAXLENGTH_NAME+1));
    if (newPerson->last_name == NULL) {
        free(newPerson);
        return NULL;
    }
    strcpy(newPerson->last_name, lastName);

    return newPerson;

}
*/

// Insert person into list of persons according to mode of arrival
int addPerson(ListPersons_t *list, Person_t *person) {

	Person_t *newPerson = person;

    // if list is empty: insert new person as first element (can be either type R or Z)
	if (list->start == NULL) {
		list->start = newPerson;
		list->last = newPerson;

	// if list ist not empty: find place for insertion depending on mode of arrival R or Z
	} else {

		Person_t *tmp = list->start;

		if (newPerson->arrival == 'R') {

			// case 1: only Zs in list! - insert R  before first Z
			if (tmp->arrival == 'Z'){
				tmp->node.prev = newPerson;
				newPerson->node.next = tmp;
				list->start = newPerson; // assign pointer to new start

            // case 2: Rs and Zs in list - insert R before first Z
			} else {
                while (tmp->arrival == 'R') { // find last person of type R
                    tmp = tmp->node.next; //
                }
                if (tmp->arrival = 'Z') { // if tmp->arrival is NOT Z, we are at end of list, skip this part
                    newPerson->node.prev = tmp->node.prev; // set last r as previous of newPerson, link between newPerson and previous element - established in newPerson
                    newPerson->node.next = tmp; // set tmp as next of newPerson, link between newPerson and following element - established in newPerson
                    tmp->node.prev->node.next = newPerson; // set of newPerson as next of last r, link between newPerson and previous element - established in previous element
                    tmp->node.prev = newPerson; // set newPerson als previous of tmp, link between newPerson and following element - established in following element
                }
            }

        // case 3: type R: only Rs in list - insert last OR case 4: type Z: always insert last
		} else {
			tmp = list->last;
			tmp->node.next = newPerson; // set newPerson als new last element
			newPerson->node.prev = tmp; // set tmp as previous element of newPerson
		    list->last = newPerson;
		}
	}
    list->count = list->count + 1;
	return 0;
}

// Move person from list - always first person
int movePerson(ListPersons_t *list) {
    if (list->start == NULL) {
        fprintf(stderr, "List is empty.\n");
        return -1;
    }
    Person_t *tmp = list->start;
    list->start = list->start->node.next;

    free(tmp->first_name);
    free(tmp->last_name);
    free(tmp);

    list->count = list->count - 1;

    return 0;
}

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
// TODO names of neighbours need to be printed correctly
void printListPersons(ListPersons_t *list) {
    Person_t *tmp = list->start;
    while (tmp != NULL) { // until end of list
        printf("Number: %d\tArrival: %c\tFirst name: %s\tLast name: %s\t",
               tmp->num, tmp->arrival, tmp->first_name, tmp->last_name);
        if (tmp->neighbour[0] == NULL) {
            printf("Neighbour 1: None.\t");
        } else {
            printf("Neighbour 1: %s %s\t", tmp->neighbour[0]->first_name,
                   tmp->neighbour[0]->last_name); // TODO is this dereferenced correctly??
        }
            if (tmp->neighbour[1] == NULL) {
                printf("Neighbour 2: None.\t");
            } else {
                printf("Neighbour 2: %s %s\t", tmp->neighbour[0]->first_name,
                       tmp->neighbour[0]->last_name); // TODO is this dereferenced correctly??
            }
            printf("\n");
            tmp = tmp->node.next; // set next element as tmp
        }
        printf("Final count: %hu\n", list->count);
    }

// Export Persons
// TODO names of neighbours need to be printed correctly
void exportListPersons(ListPersons_t *list) {

    // Create file
    FILE *fp;
    fp = fopen("export.txt", "w");

    // Check if valid pointer has been returned
    if (fp == NULL) {
        fprintf(stderr, "fopen was not successful!\n");
    }

    // Print list of persons into file
    Person_t *tmp = list->start;
    while (tmp != NULL) { // until end of list
        fprintf(fp,"Number: %d\tArrival: %c\tFirst name: %s\tLast name: %s\tSeat Number: \tNeighbour 1: \tNeighbour 2: \t",
                tmp->num, tmp->arrival, tmp->first_name, tmp->last_name);
        if (tmp->neighbour[0] == NULL) {
            fprintf(fp, "Neighbour 1: None.\t");
        } else {
            fprintf(fp,"Neighbour 1: %s %s\t", tmp->neighbour[0]->first_name,
                   tmp->neighbour[0]->last_name); // TODO is this dereferenced correctly??
        }
        if (tmp->neighbour[1] == NULL) {
            fprintf(fp, "Neighbour 2: None.\t");
        } else {
            fprintf(fp,"Neighbour 2: %s %s\t", tmp->neighbour[0]->first_name,
                   tmp->neighbour[0]->last_name); // TODO is this dereferenced correctly??
        }
        fprintf(fp, "\n");
        tmp = tmp->node.next; // set next element as tmp
    }
    fprintf(fp,"Final count: %hu\n", list->count);
    // Flush file
    if (fflush(fp) != 0) {
        fprintf(stderr, "fflush was not successful!\n");
    }
}
