#include "gtest/gtest.h"

extern "C"
{
#include "hospital_structures.h"
#include "persons.h"
	//#include "gtk3.h"
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

TEST person_unit_tests, createStructPerson_test)
{
	EXPECT_NE(createStructPerson(), nullptr);
}

TEST(person_unit_tests, createListPersons_test)
{
	EXPECT_NE(createStructPerson(), nullptr);
}

// Test if -1 is returned, once limit of active persons is reached
TEST(person_unit_tests, addPerson_limit_active_test)
{
	Person_t *newPerson = createStructPerson();
	ListPersons_t *list = createListPersons();
	list->count = 50;
	int result = 0;
	result = addPerson(list, newPerson);
	EXPECT_EQ(-1, result);
}

// Test if -1 is returned, once limit of seated persons is reached
TEST(person_unit_tests, addPerson_limit_seated_test)
{
	Person_t *newPerson = createStructPerson();
	ListPersons_t *list = createListPersons();
	list->countZivil = 25;
	result = addPerson(list, newPerson);
	EXPECT(-1, result);
}

// Test if first person is added successfully
TEST(person_unit_tests, addPerson_first_test)
{
	Person_t *newPerson = createStructPerson();
	ListPersons_t *list = createListPersons();
	result = addPerson(list, newPerson);
	EXPECT(0, result);
	EXPECT_EQ(1, list->count);
	EXPECT_EQ(list->start, newPerson);
	EXPECT_EQ(list->last, newPerson);
}

// Test if person is appended successfully
TEST(person_unit_tests, appendPerson_test)
{
	Person_t *newPerson = createStructPerson();
	ListPersons_t *list = createListPersons();
	addPerson(list, newPerson);
	result = movePerson(listActive, listCompleted);
	EXPECT(0, result);
	EXPECT_EQ(1, list->count);
}

// Test if person is moved successfully
TEST(person_unit_tests, movePerson_return_success_test)
{
	Person_t *newPerson = createStructPerson();
	ListPersons_t *listActive = createListPersons();
	ListPersons_t *listCompleted = createListPersons();
	addPerson(listActive, newPerson);
	result = movePerson(listActive, listCompleted);
	EXPECT(0, result);
	EXPECT_EQ(0, list->count);
}

// Test if -1 is returned, if list ist empty
TEST(person_unit_tests, movePerson_return_failure_test)
{
	ListPersons_t *listActive = createListPersons();
	ListPersons_t *listCompleted = createListPersons();
	result = movePerson(listActive, listCompleted);
	EXPECT(-1, result);
}

TEST(person_unit_tests, freeListPersons_test)
{
}

TEST(person_unit_tests, printPerson_test)
{
}

TEST(person_unit_tests, printListPersons_test)
{
}

TEST(person_unit_tests, exportListPersons_test)
{
}
