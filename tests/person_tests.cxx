#include "gtest/gtest.h"

extern "C"
{
#include "hospital_structures.h"
#include "persons.h"
}

// This is a dummy-test, which will always be passed. It serves as a template for other testcases
TEST(person_unit_tests, DUMMY)
{
	EXPECT_EQ(1, 1);
}
/*
//
TEST(person_unit_tests, fillStructPerson_assert_static)
{
	Person_t ref_person = {
		.num = 0,
		.arrival = 'Z',
		.first_name = "Peter",
		.last_name = "Lustig",
		.neighbour = {NULL, NULL},
		.seat = NULL,
		.node = {.next = NULL, .prev = NULL}};
	Person_t *test_person = fillStructPerson(0, 'Z', "Peter", "Lustig");
	EXPECT_EQ(ref_person.arrival, test_person->arrival);
	EXPECT_STREQ(ref_person.first_name, test_person->first_name);
	EXPECT_STREQ(ref_person.last_name, test_person->last_name);
	// NULL-Pointer kann man auch vergleichen, lass ich aber hier kurz weg
}
 */

TEST(person_unit_tests, createStructPerson_test){
    EXPECT_NE(createStructPerson(), nullptr);
}
