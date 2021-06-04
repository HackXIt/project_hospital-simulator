#ifndef PERSONS_H
#define PERSONS_H

#include "hospital_structures.h" // TODO Ask colleagues: why is it necessary to include this header here? wouldn't work otherwise

/*
 * @brief This function is responsible for creating an empty struct of person
 * @returns newStructPerson
 */
Person_t *createStructPerson();

/*
 * @brief This function creates a list of persons and starts with count = 0
 * @returns newList
 */
ListPersons_t *createListPersons();

/*
 * @brief This function fill the empty struct of person with given information
 * @param char arrival sets the arrival 'R' or 'Z'
 * @param char *first_name sets first name
 * @param char *last_name sets last name
 * @returns newPerson
 */
Person_t * fillStructPerson(char arrival, char *first_name, char *last_name);


Person_t * fillStructPersonMan(ListPersons_t *list); //TODO: Can we delete?


/*
 * @brief This function insert person into list of persons according to mode of arrival
 * @param ListPersons_t *list :
 * - if list is empty, insert new person as first element (can be either type 'R' or 'Z')
 * - if list is not empty, find place for insertion depending on mode of arrival 'R' or 'Z' but
 *   'R' has higher prioritization as 'Z'
 * @param Person_t *person : Person is added depending on the arrival in the list
 * @returns 0 in case of success, -1 in case of failure
 */
int addPerson(ListPersons_t *list, Person_t *person);


/*
 * @brief This function has to append a new person as last element to the list and delete the first
 * element if limit is reached. If the list is empty, the appended person is the first element.
 * @param Person_t *person: Person is primary appended to the list
 * @param ListPersons_t *list is the list in which the person will be appended
 * @returns 0 in case of success, -1 in case of failure
 */
int appendPerson(Person_t *person, ListPersons_t *list);


/*
 * @brief This function moves person from the list - always first person
 * @param ListPersons_t *listActive : Moves always the first element from listActive..
 * @param ListPersons_t *listCompleted : .. and appends it to listCompleted as last element.
 * @returns 0 in case of success, -1 in case of failure
 */
int movePerson(ListPersons_t *listActive, ListPersons_t *listCompleted);

/*
 * @brief Free list of persons
 * @param Person_t *person : Helps to traverse and freeing the list
 */
void freeListPersons(ListPersons_t *list);

/*
 * @brief This is a helper function for printListPersons and prints every person and its neighbours
 * @param Person_t *person : Is the person who is printed with their neighbours
 */
void printPerson(Person_t *person);

/*
 * @brief This function prints with 'printPerson(Person_t *person)' the name of the person, his neighbors
 * and the final count plus the zivil persons count of the list
 * @param Person_t *person : Is the temporary person who is printed with their neighbours
 */
void printListPersons(ListPersons_t *list);

/*
 * @brief This function export the list of persons, and works very similar to the 'printListPersons(ListPersons_t *list)'
 * but with the magnificant circumstance, that we create a file stream with timestamp in which the export will be saved (export.txt).
 * @param ListPersons_t *list : Is the person being exported with their neighbours
 */
void exportListPersons(ListPersons_t *list);

#endif
