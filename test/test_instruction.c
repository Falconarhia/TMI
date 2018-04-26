#include <instruction_list.h>
#include <ctest.h>

CTEST(INSTRUCTION_INIT, init_fail) {
	int a = init_instruction(NULL);
	int expected = -1;
	ASSERT_EQUAL(expected, a);
}

CTEST(INSTRUCTION_INIT, init_ok) {
	struct Instruction head;
	int a = init_instruction(&head);
	int expected = 0;
	ASSERT_EQUAL(expected, a);
}