#ifndef SERIALIZE_H
#define SERIALIZE_H
#include "hospital_structures.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

uint8_t *error_byte = 0xEE;
uint8_t *missing_byte = 0xAA;

/* The callback functions take a buffer, a length, and an opaque */
/* pointer which is passed through. They MUST return zero (0) on */
/* success. Any non-zero value is treated as an error and bubbled*/
/* back up to the caller. Note that "short" reads and writes   */
/* are NOT used or supported in this interface, unlike that of   */
/* read(2)/write(2).                                             */
typedef int (*raw_write_fn)(const uint8_t *bytes, size_t n, void *q);
typedef int (*raw_read_fn)(uint8_t *bytes, size_t n, void *q);

int raw_store_struct_ListRows(const struct ListRows *val, raw_write_fn w, void *q);
int raw_load_struct_ListRows(struct ListRows *val, raw_read_fn r, void *q);
int raw_store_struct_ListPersons(const struct ListPersons *val, raw_write_fn w, void *q);
int raw_load_struct_ListPersons(struct ListPersons *val, raw_read_fn r, void *q);
int raw_store_struct_Seat(const struct Seat *val, raw_write_fn w, void *q);
int raw_load_struct_Seat(struct Seat *val, raw_read_fn r, void *q);
int raw_store_struct_Person(const struct Person *val, raw_write_fn w, void *q);
int raw_load_struct_Person(struct Person *val, raw_read_fn r, void *q);
int raw_store_struct_node_s(const struct node_s *val, raw_write_fn w, void *q);
int raw_load_struct_node_s(struct node_s *val, raw_read_fn r, void *q);
int raw_store_struct_node_p(const struct node_p *val, raw_write_fn w, void *q);
int raw_load_struct_node_p(struct node_p *val, raw_read_fn r, void *q);
int raw_store_unsigned_short(const unsigned short *val, raw_write_fn w, void *q);
int raw_load_unsigned_short(unsigned short *val, raw_read_fn r, void *q);
int raw_store_char(const char *val, raw_write_fn w, void *q);
int raw_load_char(char *val, raw_read_fn r, void *q);
static inline int raw_store_ListRows_t(const ListRows_t *val, raw_write_fn w, void *q)
{
	return raw_store_struct_ListRows(val, w, q);
}
static inline int raw_store_ListPersons_t(const ListPersons_t *val, raw_write_fn w, void *q)
{
	return raw_store_struct_ListPersons(val, w, q);
}
static inline int raw_store_Seat_t(const Seat_t *val, raw_write_fn w, void *q)
{
	return raw_store_struct_Seat(val, w, q);
}
static inline int raw_store_Person_t(const Person_t *val, raw_write_fn w, void *q)
{
	return raw_store_struct_Person(val, w, q);
}
#endif