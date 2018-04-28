#include <tmi.h>
#include <ctest.h>

CTEST(TMI, init_fail) {
	int a;
	int expected;

	a = init_tmi(NULL, 10, "test/file.txt");
	expected = -1;
	ASSERT_EQUAL(expected, a);

	struct TMI tmi;

	a = init_tmi(&tmi, 10, NULL);
	expected = -1;
	ASSERT_EQUAL(expected, a);

	a = init_tmi(&tmi, 10, "file.txt");
	expected = -3;
	ASSERT_EQUAL(expected, a);

	a = init_tmi(&tmi, 10, "test/file_fail.txt");
	expected = -3;
	ASSERT_EQUAL(expected, a);
}

CTEST(TMI, init_ok) {
	int a;
	int expected;
	struct TMI tmi;

	a = init_tmi(&tmi, 10, "test/file.txt");
	expected = -0;
	ASSERT_EQUAL(expected, a);
}