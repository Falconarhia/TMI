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

int tmi_run_prev(struct TMI* tmi) {
	if(tmi == NULL) {
		return -1;
	}

	if(tmi->instruction.next == NULL) {
		return -2;
	}


	struct DLL_Node *tmp = tmi->instruction.next;

	while(tmp-> next != NULL) {
		tmp = tmp->next;
	}

	int i = 0;
	if(tmi->mt.instructions.next == NULL) {
		return -2;
	}

	struct Instruction* itmp = tmi->mt.instructions.next;
	while((itmp->next != NULL) && (i < tmp->value)){
		itmp = itmp->next;
		++i;
	}

	switch(itmp->motion) {
		case 'l':
		if(tmi->mt.cur_symbol->next != NULL) {
			tmi->mt.cur_symbol = tmi->mt.cur_symbol->next;
		}
		else {
			return -3;
		}
		break;

		case 'r':
		if(tmi->mt.cur_symbol->prev != NULL) {
			tmi->mt.cur_symbol = tmi->mt.cur_symbol->prev;
		}
		else {
			return -3;
		}
		break;

		case 's':
		break;

		default:
		return -2;
	}

	

	tmi->mt.cur_symbol->value = itmp->read_symbol;
	free(tmi->mt.cur_state);
	tmi->mt.cur_state = (char*)malloc(strlen(itmp->init_state) + 1);
	strcpy(tmi->mt.cur_state, itmp->init_state);

	remove_last(&tmi->instruction);

	return 0;
}