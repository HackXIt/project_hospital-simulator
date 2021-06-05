#ifndef QUICK_SAVE_H
#define QUICK_SAVE_H
typedef struct hospital_translators
{
	ser_tra_t *t_node_p;
	ser_tra_t *t_person;
	ser_tra_t *t_person_ref;
} hospital_tra_t;
void quick_save(ListPersons_t *active, ListPersons_t *completed);
#endif