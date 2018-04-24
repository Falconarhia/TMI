#include <double_linked_list.h>
#include <ctest.h>

CTEST(DLL_INIT, init_fail) {
	int a = init(NULL);
	int expected = -1;
	ASSERT_EQUAL(expected, a);
}

CTEST(DLL_INIT, init_ok) {
	struct DLL_Node s;
	int a = init(&s);
	int expected = 0;
	ASSERT_EQUAL(expected, a);
}

CTEST(DLL_ADD, add_fail) {
	int a = add(NULL, 1);
	int expected = -1;
	ASSERT_EQUAL(expected, a);
}

CTEST(DLL_ADD, add_ok) {
	struct DLL_Node s;
	init(&s);
	int a = add(&s, 1);
	int expected = 0;
	ASSERT_EQUAL(expected, a);
	ASSERT_EQUAL(s.next->value, 1);
}

