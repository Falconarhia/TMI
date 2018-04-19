#include "mt.h"

int init_mt(struct MT* mt, size_t len_mtape) {
	if(mt == NULL) {
		return -1;
	}


	int i = 0;
	const char* start = "start";
	mt->cur_state = (char*)malloc(strlen(start) + 1);
	strcpy(mt->cur_state, start);
	mt->stop = "stop";

	int r = init(&mt->memory_tape);

	if(r != 0) {
		return -3;
	}


	for(;i < len_mtape; ++i) {
		r = add(&mt->memory_tape, (int)(' '));
		if(r != 0) {
			return -3 + r;
		}
	}

	mt->cur_symbol = mt->memory_tape.next;
	mt->size_mtape = len_mtape;

	r = init_instruction(&mt->instructions);

	if(r != 0) {
		return -6;
	}


	return 0;
}


int add_mt_instruction(struct MT* mt, const char* cur_state, char symbol, const char* new_state, char new_symbol, char motion) {
	struct Instruction* tmp;
	if(find_instruction(&mt->instructions, &tmp, cur_state, symbol) == -4) {
		return add_instruction(&mt->instructions, cur_state, symbol, new_state, new_symbol, motion);
	} 
	return -4;
}

int run_instruction(struct MT* mt, struct Instruction* tmp) {
	if(mt == NULL) {
		return -1;
	}

	if(strcmp(mt->stop, mt->cur_state) == 0) {
		return -5;
	}
	mt->cur_symbol->value = tmp->new_symbol;
		
	if(tmp->motion == 'l') {
		if(mt->cur_symbol->prev != NULL) {
			mt->cur_symbol = mt->cur_symbol->prev;
		}
		else {
			return -2;
		}
	}
	else if(tmp->motion == 'r') {
		if(mt->cur_symbol->next != NULL) {
			mt->cur_symbol = mt->cur_symbol->next;
		}
		else {
			return -2;
		}
	}
	else if(tmp->motion != 's') {
		return -3;
	}

	free(mt->cur_state);
	mt->cur_state = (char*)malloc(strlen(tmp->new_state) + 1);
	strcpy(mt->cur_state, tmp->new_state);

	return 0;
}