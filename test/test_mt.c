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

CTEST(MT, add_fail) {
	int a;
	int expected;
	struct MT mt;

	init_mt(&mt, 10);
	add_mt_instruction(&mt, "start", 'a', "start", 'b', 'l');
	a = add_mt_instruction(&mt, "start", 'a', "start", 'b', 'l');
	expected = -4;
	ASSERT_EQUAL(expected, a);
}

CTEST(MT, add_ok) {
	int a;
	int expected;
	struct MT mt;

	init_mt(&mt, 10);
	a = add_mt_instruction(&mt, "start", 'a', "start", 'b', 'l');
	expected = 0;
	ASSERT_EQUAL(expected, a);
}

CTEST(MT, add_mt_str_fail) {
	int a;
	int expected;
	struct MT mt;

	init_mt(&mt, 10);
	a = add_mt_str(NULL, 0, "110011");
	expected = -1;
	ASSERT_EQUAL(expected, a);

	a = add_mt_str(&mt, 0, NULL);
	expected = -1;
	ASSERT_EQUAL(expected, a);

	a = add_mt_str(&mt, 0, "");
	expected = -1;
	ASSERT_EQUAL(expected, a);

	a = add_mt_str(&mt, 110, "110011");
	expected = -2;
	ASSERT_EQUAL(expected, a);
}

CTEST(MT, add_mt_str_ok) {
	int a;
	int expected;
	struct MT mt;

	init_mt(&mt, 10);
	a = add_mt_str(&mt, 0, "110011");
	expected = 0;
	ASSERT_EQUAL(expected, a);
}

CTEST(MT, run_fail) {
	int a;
	int expected;
	struct MT mt;

	init_mt(&mt, 10);
	add_mt_str(&mt, 0, "110011");
	add_mt_instruction(&mt, "start", '0', "start", '0', 't');
	add_mt_instruction(&mt, "start", '1', "start", '0', 'l');

	a = run_instruction(NULL, mt.instructions.next);
	expected = -1;
	ASSERT_EQUAL(expected, a);

	a = run_instruction(&mt, NULL);
	expected = -1;
	ASSERT_EQUAL(expected, a);

	a = run_instruction(&mt, mt.instructions.next);
	expected = -3;
	ASSERT_EQUAL(expected, a);

	a = run_instruction(&mt, mt.instructions.next->next);
	expected = -2;
	ASSERT_EQUAL(expected, a);

	free(mt.cur_state);
	mt.cur_state = "stop";
	a = run_instruction(&mt, mt.instructions.next);
	expected = -5;
	ASSERT_EQUAL(expected, a);

}

CTEST(MT, run_ok) {
	int a;
	int expected;
	struct MT mt;

	init_mt(&mt, 10);
	add_mt_str(&mt, 0, "110011");
	add_mt_instruction(&mt, "start", '1', "start", '0', 'r');

	a = run_instruction(&mt, mt.instructions.next);
	expected = 0;
	ASSERT_EQUAL(expected, a);
}