#include <stdio.h>
#include "double_linked_list.h"
#include "instruction_list.h"
#include "mt.h"
#include "parser.h"
#include "tmi.h"
#include "ncurses.h"
#include <getopt.h>
#include <pthread.h>
#include <unistd.h>

#define COL 50
#define ROW 15


struct TMI tmi;
char* filename = NULL;
int size_tape = 20000;
char c;
char v = 0;
struct DLL_Node* tape_start;
struct DLL_Node* tape_stop;
struct Instruction* ins_start;
struct Instruction* ins_stop;
char msg[50];
int delay_run = 1;
const int min_delay = 1;
const int max_delay = 100;
const int delay_step = 1;

pthread_mutex_t mut;


void* run() {
	int res;
	int flag = 0;
	char tmp[50];
	while(1) {
		if(v == 1) {
			pthread_mutex_lock(&mut);
			strcpy(msg, "                            ");
			res = tmi_run_next(&tmi, flag);
			if((res < -9) && (flag == 0))  {
				flag = 1;
				v = 0;
				sprintf(tmp, "Instruction %d. Stop", (res + 10) * (-1));
				strcpy(msg, tmp);
			}
			else if (res >= 0){
				flag = 0;
				sprintf(tmp, "Instruction %d             ", res);
				strcpy(msg, tmp);
			}
			else if(res == -5) {
				flag = 0;
				v = 0;
				strcpy(msg, "Stop                     ");
			}
			else {
				flag = 0;
				v = 0;
				strcpy(msg, "Instruction not found             ");
			}
			pthread_mutex_unlock(&mut);
		}
		sleep(delay_run);
	}
}

void init_start_stop() {
	tape_start = tmi.mt.memory_tape.next;
	tape_stop = tape_start;

	int i = 0;
	while((tape_stop->next != NULL) && (i < COL)) {
		tape_stop = tape_stop->next;
		++i;
	}

	i = 0;

	ins_start = tmi.mt.instructions.next;
	ins_stop = ins_start;

	while((ins_stop->next != NULL) && (i < ROW)) {
		ins_stop = ins_stop->next;
		++i;
	}
}

void interface() {
	struct DLL_Node* t = tape_start;
	struct Instruction* ti = ins_start;
	int x = 1;
	mvprintw(0, 20, "TMI - Turing Machine Interpreter");
	mvprintw(1, 1, "Memory tape:");
	while(t != NULL) {


		if(t == tmi.mt.cur_symbol) {
			attron(COLOR_PAIR(1));
			mvprintw(2, x, "%c", t->value);
			attroff(COLOR_PAIR(1));
		}
		else {
			mvprintw(2, x, "%c", t->value);
		}

		if(t == tape_stop) {
			break;
		}
		t = t->next;
		++x;
	}

	int y = 6;
	mvprintw(y - 1, 1, "Programm:");
	while(ti != NULL) {
		mvprintw(y, 1, "%d %s %c %s %c %c", ti->num, ti->init_state, 
			ti->read_symbol, ti->new_state, ti->new_symbol, ti->motion);
		if(ti == ins_stop) {
			break;
		}
		ti = ti->next;
		++y;
	}

	mvprintw(22, 0, "%s", msg);
	attron(COLOR_PAIR(2));
	mvprintw(1, 60, "Control panel");
	mvprintw(2, 54, "Shift tape left [a]       ");
	mvprintw(3, 54, "Shift tape right [d]      ");
	mvprintw(4, 54, "Shift instruction up [w]  ");
	mvprintw(5, 54, "Shift instruction down [s]");
	mvprintw(6, 54, "Next instruction [n]      ");
	mvprintw(7, 54, "Prev instruction [p]      ");
	mvprintw(8, 54, "Run programm [g]          ");
	mvprintw(9, 54, "Stop programm [space]     ");
	mvprintw(10, 54, "Increse delay [+]         ");
	mvprintw(11, 54, "Decrese delay [-]         ");
	mvprintw(12, 54, "Delay = %ds                ", delay_run);
	mvprintw(13, 54, "Exit [q]                  ");
	attroff(COLOR_PAIR(2));

}


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

		opt = getopt(argc, argv, ":l:f:");
	}

	res = init_tmi(&tmi, size_tape, filename);

	if(res != 0) {
		printf("Ошибка инициализации интерпретатора\n");
		return -1;
	}
	init_start_stop();

	initscr();
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_BLUE, COLOR_YELLOW);
	init_pair(2, COLOR_BLACK, COLOR_CYAN);
	noecho();

	pthread_t pt;
	char tmp[50];
	pthread_create(&pt, NULL, run, NULL);
	while(c != 'q') {
		timeout(300);
		c = getch();
		
		pthread_mutex_lock(&mut);
		switch(c) {
			case 'n':
			v = 0;
			strcpy(msg, "                            ");
			res = tmi_run_next(&tmi, 1);
			if(res == -5) {
				strcpy(msg, "Stop                       ");
			}
			else if(res == -4) {
				strcpy(msg, "Instruction not found");	
			}
			else if(res < -9)  {
				sprintf(tmp, "Instruction %d. Stop", (res + 10) * (-1));
				strcpy(msg, tmp);
			}
			else if (res >= 0){
				sprintf(tmp, "Instruction %d             ", res);
				strcpy(msg, tmp);
			}
			break;

			case 'p':
			v = 0;
			strcpy(msg, "                            ");
			res = tmi_run_prev(&tmi);
			//mvprintw(10,10, "%d", res);
			break;

			case 'r':
			v = 0;
			strcpy(msg, "                            ");
			clear_tmi(&tmi);
			res = init_tmi(&tmi, size_tape, filename);
			if(res != 0) {
				endwin();
				printf("Ошибка инициализации интерпретатора\n");
				return -1;
			}
			init_start_stop();
			break;

			case 'a':
			if(tape_start != NULL) {
				if(tape_start->prev->prev != NULL) {
					tape_stop = tape_stop->prev;
					tape_start = tape_start->prev;
				}
			}
			break;

			case 'd':
			if(tape_stop != NULL) {
				if(tape_stop->next != NULL) {
					tape_stop = tape_stop->next;
					tape_start = tape_start->next;
				}
			}
			break;

			case 'w':
			if(ins_start != NULL) {
				if(ins_start->prev->prev != NULL) {
					ins_stop = ins_stop->prev;
					ins_start = ins_start->prev;
				}
			}
			break;

			case 's':
			if(ins_stop != NULL) {
				if(ins_stop->next != NULL) {
					ins_stop = ins_stop->next;
					ins_start = ins_start->next;
				}
			}
			break;

			case '-':
			if(delay_run > min_delay) {
				delay_run -= delay_step;
			}
			break;

			case '+':
			if(delay_run < max_delay) {
				delay_run += delay_step;
			}
			break;

			case 'g':
			v = 1;
			break;

			case ' ':
			v = 0;
			break;

			default:
			break;
		}
		interface();
		pthread_mutex_unlock(&mut);
		refresh();
	}

	endwin();
	return 0;
}