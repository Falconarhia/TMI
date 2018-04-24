#include "tmi.h"

int init_tmi(struct TMI* tmi, size_t len_mtape, const char* filename) {
	if((tmi == NULL) || (filename == NULL)){
		return -1;
	}

	if((init_mt(&tmi->mt, len_mtape) != 0) ||
		(init(&tmi->instruction) != 0) ||
		(init(&tmi->breakpoint) != 0)) {
		return -2;
	}

	FILE* file = fopen(filename, "r");

	if(file == NULL) {
		return -3;
	}

	char str[SIZE_STR];
	int pos = 0;
	int p;

	while(fgets(str, SIZE_STR, file) != NULL) {
		add_mt_str(&tmi->mt, pos, str);
		p = strlen(str);
		if((p < (SIZE_STR - 1)) || (str[p - 1] == '\n')) {
			break;
		}
		pos += p;
	}
	int r;
	int i = 0;
	while(fgets(str, SIZE_STR, file) != NULL) {
		r = parser_instruction(&tmi->mt.instructions, str);
		if(r == 1) {
			add(&tmi->breakpoint, i);
		}
		else if(r != 0) {
			return -3;
		}
		++i;
	}

	return 0;

}


void clear_tmi(struct TMI* tmi) {
	clear_mt(&tmi->mt);
	clear_dll(&tmi->instruction);
	clear_dll(&tmi->breakpoint);
}


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
