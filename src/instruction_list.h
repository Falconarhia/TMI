#include "instruction_list.h"

int init_instruction(struct Instruction* head) {
	if(head == NULL) {
		return -1;
	}

	head->init_state = NULL;
	head->read_symbol = 0;
	head->new_state = NULL;
	head->new_symbol = 0;
	head->motion = 0;
	head->num = -1;
	head->next = NULL;
	head->prev = NULL;

	return 0;
}