#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

#include <stdio.h>
#include <stdlib.h>

struct DLL_Node {
	int value;
	struct  DLL_Node* prev;
	struct  DLL_Node* next;
};

int init(struct DLL_Node* head);

#endif