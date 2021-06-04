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

// occupySeat(row1, &p_1);
// occupySeat(row2, &p_2);
// occupySeat(row3, &p_3);
// occupySeat(row2, &p_4);
// occupySeat(row1, &p_5);
// occupySeat(row4, &p_6);
// occupySeat(row5, &p_7);
// occupySeat(row1, &p_8);
// occupySeat(row1, &_9);

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
	EXPECT_NE(createSeat(), nullptr);
}

// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t1)
{
	occupySeat(rows[1], &p_1);
	EXPECT_EQ(occupySeat(rows[1], &p_1), 0);
}

// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t2)
{
	occupySeat(rows[1], &p_2);
	EXPECT_EQ(occupySeat(rows[1], &p_2), 0);
}
// Not 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t3)
{
	occupySeat(rows[1], &p_3);
	EXPECT_NE(occupySeat(rows[1], &p_3), 0);
}
// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t4)
{
	occupySeat(rows[1], &p_4);
	EXPECT_EQ(occupySeat(rows[1], &p_4), 0);
}
// 0 is expected since occupying was successful
TEST(seat_rows_unit_tests, occupySeats_t5)
{
	occupySeat(rows[1], &p_5);
	EXPECT_EQ(occupySeat(rows[1], &p_5), 0);
}
// Not 0 is expected since occupying must not be successful
TEST(seat_rows_unit_tests, occupySeats_t6)
{
	occupySeat(rows[1], &p_6);
	EXPECT_NE(occupySeat(rows[1], &p_6), 0);
}
// 0 is expected for select row to be successful
TEST(seat_rows_unit_tests, selectRow_t1)
{
	EXPECT_EQ(selectRow(rows, &p_10), 0);
}

// 0 is expected for select row to be successful
TEST(seat_rows_unit_tests, selectRow_t2)
{
	EXPECT_EQ(selectRow(rows, &p_6), 0);
}
/*
// 0 is expected for select row to be successful
TEST(seat_rows_unit_tests, selectRow_t3)
{
	EXPECT_EQ(selectRow(rows, &p_3), 0);
}
*/