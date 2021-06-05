#ifndef QUICK_SAVE_H
#define QUICK_SAVE_H

#define NUM_LINES 8
typedef struct hospital_translators
{
	ser_tra_t *t_node_p;
	ser_tra_t *t_person;
	ser_tra_t *t_neighbour;
	// ser_tra_t *t_person_ref;
} hospital_tra_t;
void quick_save(ListPersons_t *active, ListPersons_t *completed, hospital_tra_t *translators);
ListPersons_t *quick_load(hospital_tra_t *translators, FILE *stream);
#endif