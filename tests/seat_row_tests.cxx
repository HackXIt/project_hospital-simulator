#include "gtest/gtest.h"


extern "C"
{
#include "seat_rows.h"
#include "hospital_structures.h" // -> Project-Datastructures
#include "persons.h"			 // -> Functions for persons & personLists


}

Person_t p_1 = {.arrival = 'Z', .first_name = "Stefan", .last_name = "Hubolt", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_2 = {.arrival = 'R', .first_name = "Patrick", .last_name = "Culies", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_3 = {.arrival = 'R', .first_name = "Sandra", .last_name = "Humar", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_4 = {.arrival = 'R', .first_name = "Ricardo", .last_name = "Monatez", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_5 = {.arrival = 'R', .first_name = "Petra", .last_name = "Turner", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_6 = {.arrival = 'R', .first_name = "Luigi", .last_name = "Pomodoro", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_7 = {.arrival = 'R', .first_name = "Franklin", .last_name = "Domali", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_8 = {.arrival = 'R', .first_name = "Malcolm", .last_name = "Mehves", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_9 = {.arrival = 'R', .first_name = "Fillin", .last_name = "Kasper", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};
Person_t p_10 = {.arrival = 'R', .first_name = "Afua", .last_name = "Mara", .neighbour = {NULL, NULL}, .seat = NULL, .node = {.next = NULL, .prev = NULL}};

ListRows_t *row1 = createRow();
ListRows_t *row2 = createRow();
ListRows_t *row3 = createRow();
ListRows_t *row4 = createRow();
ListRows_t *row5 = createRow();

ListRows_t *rows[5] = {row1, row2, row3, row4, row5};

occupySeat(row1, &p_1);
occupySeat(row2, &p_2);
occupySeat(row3, &p_3);
occupySeat(row2, &p_4);
occupySeat(row1, &p_5);
occupySeat(row4, &p_6);
occupySeat(row5, &p_7);
occupySeat(row1, &p_8);
occupySeat(row1, &_9);


// This is a dummy-test, which will always be passed. It serves as a template for other testcases
TEST(seat_rows_unit_tests, DUMMY)
{
	EXPECT_EQ(1, 1);
}


// Not NULL is expected if the seat was successful created
TEST(seat_rows_unit_tests, createSeat ) {
    EXPECT_NE(createSeat(), NULL);
}

// Not NULL is expected if the row was successful created
TEST(seat_rows_unit_tests, createRow ) {
    EXPECT_NE(createSeat(), NULL);
}


// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t1 ){
        occupySeat(row[1], &p_1 ) ;
        EXPECT_EQ(occupySeat(row[1], &p_1), 0);
    }
}
// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t2 ){
           occupySeat(row[1], &p_2 ) ;
        EXPECT_EQ(occupySeat(row[1], &p_2), 0);
}
// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t3 ){
        occupySeat(row[1], &p_3 ) ;
        EXPECT_EQ(occupySeat(row[1], &p_3), 0);
}
// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t4 ){
    for(int i = 1; i <= 5; i ++) {
        occupySeat(row[1], &p_4 ) ;
        EXPECT_EQ(occupySeat(row[1], &p_4), 0);
    }
}
// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t5 ){
    for(int i = 1; i <= 5; i ++) {
        occupySeat(row[1], &p_5 ) ;
        EXPECT_EQ(occupySeat(row[1], &p_5), 0);
    }
}
// Not 0 is expected since occupying must not be successful
TEST(seat_rows_unit_tests, occupySeats_t5 ){
    for(int i = 1; i <= 5; i ++) {
        occupySeat(row[1], &p_6 ) ;
        EXPECT_NE(occupySeat(row[1], &p_6 ), 0);
    }
}

TEST(seat_rows_unit_tests, selectRow ) {
EXPECT_EQ(selectRow(rows, &p_10), 0);
}




