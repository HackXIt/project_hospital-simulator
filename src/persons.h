#ifndef PERSONS_H
#define PERSONS_H

#include "hospital_structures.h" // TODO Ask colleagues: why is it necessary to include this header here? wouldn't work otherwise

Person_t *createStructPerson();
ListPersons_t *createListPersons();
Person_t * fillStructPerson(unsigned short num, char arrival, char *first_name, char *last_name);
int addPerson(ListPersons_t *list, Person_t *person);
void freeListPersons(ListPersons_t *list);
void printListPersons(ListPersons_t *list);

#endif
