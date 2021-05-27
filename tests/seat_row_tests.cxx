#include "gtest/gtest.h"
#include "seat_rows.h"

extern "C"
{
#include "seat_rows.h"
#include "persons.h"
}

/*
	Person_t ref_person = {
		.arrival = 'Z',
		.first_name = "Peter",
		.last_name = "Lustig",
		.neighbour = {NULL, NULL},
		.seat = NULL,
		.node = {.next = NULL, .prev = NULL}};
	//Person_t *test_person = fillStructPerson('Z', "Peter", "Lustig");
 */
Person_t p_1 = {.arrival = 'Z', .first_name = "Stefan", .last_name = "Hubolt", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_2 = {.arrival = 'R', .first_name = "Stefan", .last_name = "Hubolt", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_3 = {.arrival = 'O', .first_name = "Stefan", .last_name = "Hubolt", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};

/*
TEST(seat_rows_unit_tests, createRow)
{
EXPECT_EQ(createRow(), NULL);
}
*/
TEST(seat_rows_unit_tests, addPersontoRow)
{

    ListRows_t *row1 = createRow();
    occupySeat(row1, &p_1);
    Seat_t *current = rows[i - 1 ]->start; //why rows[i -1 ] ??
    if ( current->occupied != NULL) {
        printf("Name: %s %s \n", current->occupied->first_name, current->occupied->last_name );
    } else {
        printf("<NULL>\n");
    }

}


// This is a dummy-test, which will always be passed. It serves as a template for other testcases
TEST(seat_rows_unit_tests, DUMMY)
{
	EXPECT_EQ(1, 1);
}
