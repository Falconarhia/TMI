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

int add(struct DLL_Node* head, int value) {
	if(head == NULL) {
		return -1;
	}

	while(head->next != NULL) {
		head = head->next;
	}

	struct DLL_Node* tmp = (struct DLL_Node*) malloc(sizeof(struct DLL_Node));

	if(tmp == NULL) {
		return -2;
	}

	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = head;
	head->next = tmp;

	return 0;
}