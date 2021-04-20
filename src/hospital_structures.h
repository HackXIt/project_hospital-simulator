#ifndef HOSPITAL_STRUCTURES_H
#define HOSPITAL_STRUCTURES_H

struct node
{
    void *next;
    void *prev;
};

typedef struct Person
{
    unsigned short num;
    char arrival; // Valid arrivals are: Z, R, (K is optional)
    char *first_name;
    char *last_name;
    struct Person *neighbour[2]; // storage of left & right neighbour
    struct Seat *seat;           // reference to seat, if any
    struct node;
} Person_t;

typedef struct Seat
{
    struct Person *occupied; // if occupied != NULL then it is occupied
    struct node;
} Seat_t;

typedef struct ListPersons
{
    unsigned short count;
    struct Person *start;
    struct Person *last;
} ListPersons_t;

typedef struct ListRows
{
    unsigned short count;
    struct Seat *start;
    struct Seat *last;
<<<<<<< HEAD
}
=======
} ListRows_t;
>>>>>>> nick
#endif