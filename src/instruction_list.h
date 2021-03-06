#ifndef INSTRUCTION_LIST
#define INSTRUCTION_LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Instruction {
	char* init_state;
	char read_symbol;
	char* new_state;
	char new_symbol;
	char motion;
	int num;
	struct Instruction* next;
	struct Instruction* prev;
};

int init_instruction(struct Instruction* head);
int add_instruction(struct Instruction* head, const char* init_state, char read_symbol, const char* new_state, char new_symbol, char motion);
int remove_last_instruction(struct Instruction* head);
int find_instruction(struct Instruction* head, struct Instruction** f_node, const char* init_state, char read_symbol);
void clear_instruction(struct Instruction* head);
#endif
