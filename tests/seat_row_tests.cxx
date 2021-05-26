#include "gtest/gtest.h"

extern "C"
{
#include "seat_rows.h"
}

// This is a dummy-test, which will always be passed. It serves as a template for other testcases
TEST(seat_rows_unit_tests, DUMMY)
{
	EXPECT_EQ(1, 1);
}