#include "gtest/gtest.h"

extern "C"
{
#include "gtk3.h"
}

// This is a dummy-test, which will always be passed. It serves as a template for other testcases
TEST(gui_unit_tests, DUMMY)
{
	EXPECT_EQ(1, 1);
}