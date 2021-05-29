#ifndef HOSPITAL_STRUCTURES_H
#define HOSPITAL_STRUCTURES_H

#define SUCCESS 1
#define FAILURE 0

struct node_p
{
	struct Person *next;
	struct Person *prev;
};
struct node_s
{
	struct Seat *next;
	struct Seat *prev;
};

typedef struct Person
{
	char arrival; // Valid arrivals are: Z, R, (K is optional)
	char *first_name;
	char *last_name;
	struct Person *neighbour[2]; // storage of left & right neighbour
	struct Seat *seat;			 // reference to seat, if any
	struct ListRows *row;		 // reference to row of the seat
	struct node_p node;
} Person_t;

typedef struct Seat
{
	struct Person *occupied; // if 'occupied != NULL' then it is occupied
	struct node_s node;
} Seat_t;

typedef struct ListPersons // There is an active & completed list
{
	unsigned short count;
	unsigned short countZivil; // This is for counting 'seated' Persons, since there are only a limited number of seats
	struct Person *start;
	struct Person *last;
} ListPersons_t;

typedef struct ListRows // There are 5 rows in the hospital
{
	unsigned short count;
	struct Seat *start;
	struct Seat *last;
} ListRows_t;
#endif