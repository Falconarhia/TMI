#include "parser.h"

int is_printed_char(char c) {
	if((c >= '!') && (c <= '~')) {
		return 0;
	}
	return -1;
}


int parser_instruction(struct Instruction* instruction, const char* str) {
	if(instruction == NULL) {
		return -1;
	}

	if(str == NULL) {
		return -2;
	}

	if(str[0] == '\0') {
		return -2;
	}

	int state = 1;
	char init_state[100];
	char new_state[100];
	int flag = 0;
	char sc;
	char nc;
	char m;
	int i = 0;
	int j = 0;

	while((str[i] != '\0') && (str[i] != '\n') && (str[i] != '\r')) {
		switch(state) {
			case 2:
			if(str[i] == ' ') {
				init_state[j] = '\0';
				state = 3;
				j = 0;
				break;
			}
			case 1:
			if(is_printed_char(str[i]) == 0) {
				init_state[j] = str[i];
				state = 2;
			}
			else {
				return -3;
			}
			++j;
			break;

			case 3:
			if(is_printed_char(str[i]) == 0) {
				sc = str[i];
				state = 4;
			}
			else {
				return -3;
			}
			break;

			case 4:
			if(str[i] == ' '){
				state = 5;
			}
			else if((sc == 'l') && (str[i] == 'b')) {
				sc = ' ';
			}
			else {
				return -3;
			}
			flag = 0;
			break;

			case 6:
			if(str[i] == ' ') {
				new_state[j] = '\0';
				state = 7;
				j = 0;
				break;
			}
			case 5:
			if(is_printed_char(str[i]) == 0) {
				new_state[j] = str[i];
				state = 6;
			}
			else {
				return -3;
			}
			++j;
			break;

			case 7:
			if(is_printed_char(str[i]) == 0) {
				nc = str[i];
				state = 8;
			}
			else {
				return -3;
			}
			break;

			case 8:
			if(str[i] == ' ') {
				state = 9;
			}
			else if((nc == 'l') && (str[i] == 'b')) {
				nc = ' ';
			}
			else {
				return -3;
			}
			break;

			case 9:
			if((str[i] == 'l') || (str[i] == 'r') || (str[i] == 's')) {
				m = str[i];
				state = 10;
			}
			else {
				return -3;
			}
			break;

			case 10:
			if(str[i] == '!'){
				state = 11;
			}
			else {
				return -3;
			}
			break;

			default:
			return -3;
		}
		++i;
	}

	if(add_instruction(instruction, init_state, sc, new_state, nc, m) != 0) {
		return -1;
	}
	if(state == 10) {
		return 0;
	}

	if(state == 11) {
		return 1;
	}

	return -3;
}