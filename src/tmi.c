#include "tmi.h"

int tmi_run_next(struct TMI* tmi, int flag) {
	if(tmi == NULL) {
		return -1;
	}

	if(strcmp(tmi->mt.stop, tmi->mt.cur_state) == 0) {
		return -5;
	}
	struct Instruction* tmp;
	struct DLL_Node* tmpb;
	int r = find_instruction(&tmi->mt.instructions, &tmp, tmi->mt.cur_state, tmi->mt.cur_symbol->value);
	if(r > -1) {
		if((flag == 0) && (find_item(&tmi->breakpoint, r) != NULL)) {
			return -10 - r;
		}
		if(run_instruction(&tmi->mt, tmp) == 0){
			add(&tmi->instruction, r);
			return r;
		}
	}
	return -4;
}