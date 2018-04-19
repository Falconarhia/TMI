#include "mt.h"

void clear_mt(struct MT* mt) {
	clear_dll(&mt->memory_tape);
	clear_instruction(&mt->instructions);
	free(mt->cur_state);
	mt->cur_state = NULL;
}