#include "double_linked_list.h"

int init(struct DLL_Node* head) {
	if(head == NULL) {
		return -1;
	}

	head->value = 0;
	head->prev = NULL;
	head->next = NULL;
	return 0;
}