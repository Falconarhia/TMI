#include <stdio.h>
#include "double_linked_list.h"
#include "instruction_list.h"
#include "mt.h"
#include "parser.h"
#include "tmi.h"
#include "ncurses.h"
#include <getopt.h>

struct TMI tmi;
char* filename = NULL;
int size_tape = 20000;

int main (int argc, char** argv) {
	if(argc > 3) {
		printf("Слишко много параметров\n");
		return -1;
	}
	if(argc == 1) {
		printf("Слишко мало параметров\n");
		return -1;
	}

	int res = 0;
	int opt = getopt(argc, argv, ":l:f:");
	while(opt != -1) {
		switch(opt) {
			case 'l':
			if(res != 0) {
				printf("Нельзя повторнно использовать параметр l\n");
				return -1;
			}
			res = sscanf(optarg, "%d", &size_tape);
			if((size_tape < 1) || (res < 1)){
				printf("Неверно задана длина ленты\n");
				return -1;
			}
			break;

			case 'f':
			if(filename != NULL) {
				printf("Нельзя повторно использовать параметр f\n");
				return -1;
			}
			filename = (char*) malloc(strlen(optarg) + 1);
			strcpy(filename, optarg);
			break;

			default:
			printf("Неизвестный параметр\n");
			return -1;
		}
		printf("%s\n", optarg);
		opt = getopt(argc, argv, ":l:f:");
	}
	return 0;
}