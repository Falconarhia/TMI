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