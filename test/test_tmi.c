#include <tmi.h>
#include <ctest.h>

CTEST(TMI, init_fail) {
	int a;
	int expected;

	a = init_tmi(NULL, 10, "examples/file.txt");
	expected = -1;
	ASSERT_EQUAL(expected, a);

	struct TMI tmi;

	a = init_tmi(&tmi, 10, NULL);
	expected = -1;
	ASSERT_EQUAL(expected, a);

	a = init_tmi(&tmi, 10, "file.txt");
	expected = -3;
	ASSERT_EQUAL(expected, a);

	a = init_tmi(&tmi, 10, "examples/file_fail.txt");
	expected = -3;
	ASSERT_EQUAL(expected, a);
}

CTEST(TMI, init_ok) {
	int a;
	int expected;
	struct TMI tmi;

	a = init_tmi(&tmi, 10, "examples/file.txt");
	expected = 0;
	ASSERT_EQUAL(expected, a);
}

CTEST(TMI, run_next_fail) {
	int a;
	int expected;
	struct TMI tmi;

	init_tmi(&tmi, 1000, "examples/file_run_fail.txt");
	expected = -4;

	a = tmi_run_next(&tmi, 0);
	ASSERT_EQUAL(expected, a);

	a = tmi_run_next(NULL, 0);
	expected = -1;
	ASSERT_EQUAL(expected, a);

	free(tmi.mt.cur_state);
	tmi.mt.cur_state = "stop";
	a = tmi_run_next(&tmi, 0);
	expected = -5;
	ASSERT_EQUAL(expected, a);
}

CTEST(TMI, run_next_ok) {
	int a;
	int expected;
	struct TMI tmi;

	init_tmi(&tmi, 1000, "examples/file.txt");
	expected = 0;

	a = tmi_run_next(&tmi, 0);
	ASSERT_EQUAL(expected, a);

	expected = -11;
	a = tmi_run_next(&tmi, 0);
	ASSERT_EQUAL(expected, a);
}

CTEST(TMI, run_prev_ok) {
	int a;
	int expected;
	struct TMI tmi;

	init_tmi(&tmi, 1000, "examples/file.txt");
	tmi_run_next(&tmi, 0);
	tmi_run_next(&tmi, 0);

	expected = 0;
	a = tmi_run_prev(&tmi);
	ASSERT_EQUAL(expected, a);
}

CTEST(TMI, run_prev_fail) {
	int a;
	int expected;
	struct TMI tmi;

	init_tmi(&tmi, 1000, "examples/file.txt");

	expected = -2;
	a = tmi_run_prev(&tmi);
	ASSERT_EQUAL(expected, a);
	
	tmi_run_next(&tmi, 0);
	tmi_run_next(&tmi, 0);

	expected = -1;
	a = tmi_run_prev(NULL);
	ASSERT_EQUAL(expected, a);
}