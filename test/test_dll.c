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

