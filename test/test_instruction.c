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

CTEST(INSTRUCTION_ADD, add_fail) {
	struct Instruction head;
	init_instruction(&head);
	int a = add_instruction(NULL, "qwe", 'a', "eqw", 'd', 'r');
	int expected = -1;
	ASSERT_EQUAL(expected, a);
	a = add_instruction(&head, NULL, 'a', "eqw", 'd', 'r');
	expected = -2;
	ASSERT_EQUAL(expected, a);
}

CTEST(INSTRUCTION_ADD, add_ok) {
	struct Instruction head;
	init_instruction(&head);
	int a = add_instruction(&head, "qwe", 'a', "eqw", 'd', 'r');
	int expected = 0;
	ASSERT_EQUAL(expected, a);
}


CTEST(INSTRUCTION_REMOVE, remove_fail) {
	int a = remove_last_instruction(NULL);
	int expected = -1;
	ASSERT_EQUAL(expected, a);
}

CTEST(INSTRUCTION_REMOVE, remove_empty) {
	struct Instruction head;
	init_instruction(&head);
	int a = remove_last_instruction(&head);
	int expected = -2;
	ASSERT_EQUAL(expected, a);
}

CTEST(INSTRUCTION_REMOVE, remove_ok) {
	struct Instruction head;
	init_instruction(&head);
	add_instruction(&head, "qwe", 'a', "eqw", 'd', 'r');
	int a = remove_last_instruction(&head);
	int expected = 0;
	ASSERT_EQUAL(expected, a);
}

CTEST(INSTRUCTION_FIND, find_fail) {
	struct Instruction head;
	struct Instruction* tmp;
	init_instruction(&head);
	add_instruction(&head, "qwe", 'a', "eqw", 'd', 'r');
	int a = find_instruction(NULL, &tmp, "qwe", 'a');
	int expected = -1;
	ASSERT_EQUAL(expected, a);
	a = find_instruction(&head, NULL, "qwe", 'a');
	expected = -2;
	ASSERT_EQUAL(expected, a);
	a = find_instruction(&head, &tmp, NULL, 'a');
	expected = -3;
	ASSERT_EQUAL(expected, a);
	a = find_instruction(&head, &tmp, "ddqwd", 'a');
	expected = -4;
	ASSERT_EQUAL(expected, a);
}


CTEST(INSTRUCTION_FIND, find_ok) {
	struct Instruction head;
	struct Instruction* tmp;
	init_instruction(&head);
	add_instruction(&head, "qwe", 'a', "eqw", 'd', 'r');
	int a = find_instruction(&head, &tmp, "qwe", 'a');
	int expected = 0;
	ASSERT_EQUAL(expected, a);
}
