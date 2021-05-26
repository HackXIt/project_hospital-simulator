#include "gtest/gtest.h"

extern "C"
{
#include "persons.h"
}

// This is a dummy-test, which will always be passed. It serves as a template for other testcases
TEST(person_unit_tests, DUMMY)
{
	EXPECT_EQ(1, 1);
}