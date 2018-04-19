#ifndef  MT_H
#define MT_H

#include <stdio.h>
#include "double_linked_list.h"
#include "instruction_list.h"

struct MT {
	struct DLL_Node memory_tape;
	struct Instruction instructions;
	char* cur_state;
	char* stop;
	struct DLL_Node* cur_symbol;
	size_t size_mtape;
};

int init_mt(struct MT* mt, size_t len_mtape);
int add_mt_instruction(struct MT* mt, const char* cur_state, char symbol, const char* new_state, char new_symbol, char motion);
int run_instruction(struct MT* mt, struct Instruction* tmp);

#endif