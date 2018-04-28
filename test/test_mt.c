#include <mt.h>
#include <ctest.h>

CTEST(MT, init_fail) {
	int a;
	int expected;

	a = init_mt(NULL, 10);
	expected = -1;
	ASSERT_EQUAL(expected, a);

	struct MT mt;
	a = init_mt(&mt, 0);
	expected = -1;
	ASSERT_EQUAL(expected, a);
}

CTEST(MT, init_ok) {
	int a;
	int expected;
	struct MT mt;

	a = init_mt(&mt, 10);
	expected = 0;
	ASSERT_EQUAL(expected, a);
}