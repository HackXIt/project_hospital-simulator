#ifndef SEAT_ROWS_H
#define SEAT_ROWS_H

#ifndef MAX_ROWS
#define MAX_ROWS 5
#endif

ListRows_t *createRow();
int occupySeat(ListRows_t *row, Person_t *person);
// int assignSeat(ListRows_t *row, Person_t *person);
int selectRow(ListRows_t *rows[MAX_ROWS], Person_t *person);
int freeRow(ListRows_t *row);
int freeSeat(Seat_t *seat);

#endif