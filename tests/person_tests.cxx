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

TEST(person_unit_tests, fillStructPerson_assert_static)
{
	Person_t ref_person = {
		.arrival = 'Z',
		.first_name = "Peter",
		.last_name = "Lustig",
		.neighbour = {NULL, NULL},
		.seat = NULL,
		.node = {.next = NULL, .prev = NULL}};
	Person_t *test_person = fillStructPerson('Z', "Peter", "Lustig");
	EXPECT_EQ(ref_person.arrival, test_person->arrival);
	EXPECT_STREQ(ref_person.first_name, test_person->first_name);
	EXPECT_STREQ(ref_person.last_name, test_person->last_name);
}

TEST(person_unit_tests, createStructPerson_test){
    EXPECT_NE(createStructPerson(), nullptr);
}

TEST(person_unit_tests, createListPersons_test){
    EXPECT_NE(createStructPerson(), nullptr);
}

// Test if -1 is returned, once limit of active persons is reached
TEST(person_unit_tests, addPerson_limit_active_test){
    Person_t *newPerson = createStructPerson();
    ListPersons_t *list = createListPersons();
    list->count = 50;
    EXPECT_EQ(addPerson(list, newPerson), -1);
}

// Test if -1 is returned, once limit of seated persons is reached
TEST(person_unit_tests, addPerson_limit_seated_test){
    Person_t *newPerson = createStructPerson();
    ListPersons_t *list = createListPersons();
    newPerson->arrival = 'Z';
    list->countZivil = 25;
    EXPECT_EQ(addPerson(list, newPerson), -1);
}
/*
// Test if first person is added successfully
TEST(person_unit_tests, addPerson_first_test){
    Person_t * newPerson = createStructPerson();
    ListPersons_t *list = createListPersons();
    EXPECT_EQ(list->start, list->last);
}
*/
