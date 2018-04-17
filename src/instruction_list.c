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

int add_instruction(struct Instruction* head, const char* init_state, char read_symbol, 
					const char* new_state, char new_symbol, char motion) {

	if(head == NULL) {
		return -1;
	}

	if((init_state == NULL) || (new_state == NULL)){
		return -2;
	}

	while(head->next != NULL) {
		head = head->next;
	}

	struct Instruction* tmp = (struct Instruction*) malloc(sizeof(struct Instruction));

	if(tmp == NULL) {
		return -3;
	}

	int len = strlen(init_state);
	tmp->init_state = (char*)malloc(len + 1);

	if(tmp->init_state == NULL) {
		free(tmp);
		return -3;
	}

	strcpy(tmp->init_state, init_state);

	len = strlen(new_state);
	tmp->new_state = (char*)malloc(len + 1);

	if(tmp->new_state == NULL) {
		free(tmp->init_state);
		free(tmp);
		return -3;
	}

	strcpy(tmp->new_state, new_state);

	tmp->read_symbol = read_symbol;
	tmp->new_symbol = new_symbol;
	tmp->motion = motion;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->num = head->num + 1;
	head->next = tmp;

	return 0;
}