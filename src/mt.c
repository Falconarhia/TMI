#include "mt.h"

void clear_mt(struct MT* mt) {
	clear_dll(&mt->memory_tape);
	clear_instruction(&mt->instructions);
	free(mt->cur_state);
	mt->cur_state = NULL;
}

int add_mt_str(struct MT* mt, size_t pos, const char *str) {
	if(mt == NULL) {
		return -1;
	}

	if(str == NULL) {
		return -1;
	}

	if(str[0] == '\0') {
		return -1;
	}

	if(pos >= mt->size_mtape) {
		return -2;
	}

	struct DLL_Node* tmp = mt->memory_tape.next;
	int p = 0;

	while((tmp != NULL) && (pos > p)) {
		tmp = tmp-> next;
		++p;
	}
	int i = 0;
	while((tmp != NULL) && (str[i] != '\0') && (str[i] != '\n')) {
		tmp->value = (int)str[i];
		tmp = tmp->next;
		++i;
	}

	return 0;
}