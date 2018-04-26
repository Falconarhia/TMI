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
	a = parser(NULL, "start 1 start 0 r");
	expected = -1;
	ASSERT_EQUAL(expected, a);
}