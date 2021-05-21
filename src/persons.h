#ifndef PERSONS_H
#define PERSONS_H

#include "hospital_structures.h" // TODO Ask colleagues: why is it necessary to include this header here? wouldn't work otherwise

Person_t *createStructPerson();
ListPersons_t *createListPersons();
Person_t * fillStructPerson(unsigned short num, char arrival, char *first_name, char *last_name);
Person_t * fillStructPersonMan(ListPersons_t *list);
int addPerson(ListPersons_t *list, Person_t *person);
int movePerson(ListPersons_t *listActive, ListPersons_t *listCompleted);
int appendPerson(Person_t *person, ListPersons_t *list);
void freeListPersons(ListPersons_t *list);
void printPerson(Person_t *person);
void printListPersons(ListPersons_t *list);
void exportListPersons(ListPersons_t *list);

#endif
