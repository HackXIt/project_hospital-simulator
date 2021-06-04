#include "gtest/gtest.h"

extern "C"
{
#include "hospital_structures.h" // -> Project-Datastructures
#include "seat_rows.h"
#include "persons.h" // -> Functions for persons & personLists
}

Person_t p_1 = {.arrival = 'Z', .first_name = "Stefan", .last_name = "Hubolt", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};
Person_t p_2 = {.arrival = 'R', .first_name = "Patrick", .last_name = "Culies", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};
Person_t p_3 = {.arrival = 'R', .first_name = "Sandra", .last_name = "Humar", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};
Person_t p_4 = {.arrival = 'R', .first_name = "Ricardo", .last_name = "Monatez", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};
Person_t p_5 = {.arrival = 'R', .first_name = "Petra", .last_name = "Turner", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};
Person_t p_6 = {.arrival = 'R', .first_name = "Luigi", .last_name = "Pomodoro", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};
Person_t p_7 = {.arrival = 'R', .first_name = "Franklin", .last_name = "Domali", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};
Person_t p_8 = {.arrival = 'R', .first_name = "Malcolm", .last_name = "Mehves", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};
Person_t p_9 = {.arrival = 'R', .first_name = "Fillin", .last_name = "Kasper", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};
Person_t p_10 = {.arrival = 'R', .first_name = "Afua", .last_name = "Mara", .neighbour = {nullptr, nullptr}, .seat = nullptr, .node = {.next = nullptr, .prev = nullptr}};

ListRows_t *row1 = createRow();

ListRows_t *row2 = createRow();
ListRows_t *row3 = createRow();
ListRows_t *row4 = createRow();
ListRows_t *row5 = createRow();

ListRows_t *rows[5] = {row1, row2, row3, row4, row5};


// This is a dummy-test, which will always be passed. It serves as a template for other testcases
TEST(seat_rows_unit_tests, DUMMY)
{
	EXPECT_EQ(1, 1);
}

// Not nullptr is expected if the seat was successful created
TEST(seat_rows_unit_tests, createSeat)
{
	EXPECT_NE(createSeat(), nullptr);
}

// Not nullptr is expected if the row was successful created
TEST(seat_rows_unit_tests, createRow)
{
   EXPECT_NE(createRow(), nullptr);
}

TEST(seat_rows_unit_tests, createRow_2)
{
    ListRows_t *row_t = createRow();
    EXPECT_EQ(row_t->count, 0) ;
    EXPECT_NE(row_t->start, nullptr);
    EXPECT_NE( row_t->start, row_t->last);
}


// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t1)
{
	occupySeat(rows[1], &p_1);
	printf("The current place has the count: %d\n", row1->count);
	EXPECT_EQ(occupySeat(rows[1], &p_1), 0);
}

// 0 is expected for select row to be successful
TEST(seat_rows_unit_tests, selectRow_t1)
{
    selectRow(rows, &p_1);
    printf("The first name of the person p_1 is %s\t", p_1.first_name);
    printf( "The last name of the son p_1 is %s\t", p_2.last_name);
   /*
    printf("Neighbour 1: %s %s\t", p_1.neighbour[0]->first_name, p_1.neighbour[0]->last_name);
    printf( "Neighbour 2: %s %s\t", p_1.neighbour[1]->last_name, p_1.neighbour[1]->last_name);
    printf("The current place has the count: %d\n", row1->count);
    printf("The next person p_1 is %s \n", p_1.node.next->first_name, p_1.node.next->last_name);
    printf("The previous person p_1 is %s \n", p_1.node.prev->first_name, p_1.node.prev->last_name);
    printf("The current place has the count: %d\n", row1->count);

*/
}

// 0 is expected for select row to be successful
TEST(seat_rows_unit_tests, selectRow_t2)
{
    EXPECT_EQ(selectRow(rows, &p_1), 0);
    EXPECT_EQ(selectRow(rows, &p_2), 0);
	EXPECT_EQ(selectRow(rows, &p_3), 1);
    EXPECT_EQ(selectRow(rows, &p_4), 1);
    EXPECT_EQ(selectRow(rows, &p_5), 1);
    EXPECT_EQ(selectRow(rows, &p_6), 0);
    EXPECT_EQ(selectRow(rows, &p_7), 0);
    EXPECT_EQ(selectRow(rows, &p_8), 0);
    EXPECT_EQ(selectRow(rows, &p_9), 0);
    EXPECT_EQ(selectRow(rows, &p_10), 0);

    EXPECT_EQ(selectRow(rows, &p_1), 0);
    EXPECT_EQ(selectRow(rows, &p_2), 0);
    EXPECT_EQ(selectRow(rows, &p_3), 0);
    EXPECT_EQ(selectRow(rows, &p_4), 0);
    EXPECT_EQ(selectRow(rows, &p_5), 0);
    EXPECT_EQ(selectRow(rows, &p_6), 0);
    EXPECT_EQ(selectRow(rows, &p_7), 0);
    EXPECT_EQ(selectRow(rows, &p_8), 0);
    EXPECT_EQ(selectRow(rows, &p_9), 0);
    EXPECT_EQ(selectRow(rows, &p_10), 0);

    EXPECT_EQ(selectRow(rows, &p_1), 0);
    EXPECT_EQ(selectRow(rows, &p_2), 0);
    EXPECT_EQ(selectRow(rows, &p_3), 0);
    EXPECT_EQ(selectRow(rows, &p_4), 0);
    EXPECT_EQ(selectRow(rows, &p_5), 0);

}


