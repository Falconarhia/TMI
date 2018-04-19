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