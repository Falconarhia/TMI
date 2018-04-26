#include <parser.h>
#include <ctest.h>

CTEST(IS_PRINTED_CHAR, fail) {
	int a = is_printed_char( (char)10 );
	int expected = -1;
	ASSERT_EQUAL(expected, a);
}

CTEST(IS_PRINTED_CHAR, ok) {
	int a = is_printed_char('1');
	int expected = 0;
	ASSERT_EQUAL(expected, a);
}

CTEST(PARSER, parser_fail) {
	int a;
	int expected;
	a = parser_instruction(NULL, "start 1 start 0 r");
	expected = -1;
	ASSERT_EQUAL(expected, a);

	struct Instruction head;
	init_instruction(&head);

	a = parser_instruction(&head, NULL);
	expected = -2;
	ASSERT_EQUAL(expected, a);

	a = parser_instruction(&head, "");
	expected = -2;
	ASSERT_EQUAL(expected, a);

	a = parser_instruction(&head, "asdadqwd");
	expected = -3;
	ASSERT_EQUAL(expected, a);
}

CTEST(PARSER, parser_ok) {
	int a;
	int expected;
	struct Instruction head;
	init_instruction(&head);

	a = parser_instruction(&head, "start 1 start 0 r");
	expected = 0;
	ASSERT_EQUAL(expected, a);

	a = parser_instruction(&head, "start 1 start 0 l!");
	expected = 1;
	ASSERT_EQUAL(expected, a);
}