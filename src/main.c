#include <stdio.h>
#include "double_linked_list.h"
#include "instruction_list.h"
#include "mt.h"
#include "parser.h"
#include "tmi.h"

int main (int argc, const char** argv) {
	struct TMI tmi;
	int r = init_tmi(&tmi, 20000, argv[1]);
	printf("init %d\n", r);

	struct Instruction* i_tmp = tmi.mt.instructions.next;

	while(i_tmp != NULL) {
		printf("print instruction %s %c %s %c %c\n", i_tmp->init_state, i_tmp->read_symbol, i_tmp->new_state, i_tmp->new_symbol, i_tmp->motion);
		i_tmp = i_tmp->next;
	}

	struct DLL_Node *d = &tmi.mt.memory_tape;
	r = tmi_run_next(&tmi, 0);
	while((r > -1) || (r < -9)){
		printf("tmi_run_next %d\n", r);
		d = &tmi.mt.memory_tape;
		while((d != NULL) && (d->value != ' ')) {
			printf("%c", (char)d->value);
			d = d->next;
		}
		printf("\n");
		if(r < -9) {
			r = tmi_run_next(&tmi, 1);
		}
		else {
			r = tmi_run_next(&tmi, 0);	
		}
	}

	printf("%d\n", r);

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	clear_tmi(&tmi);
	r = init_tmi(&tmi, 20000, argv[1]);
	printf("init %d\n", r);

	d = &tmi.mt.memory_tape;
	r = tmi_run_next(&tmi, 0);
	while((r > -1) || (r < -9)){
		printf("tmi_run_next %d\n", r);
		d = &tmi.mt.memory_tape;
		while((d != NULL) && (d->value != ' ')) {
			printf("%c", (char)d->value);
			d = d->next;
		}
		printf("\n");
		if(r < -9) {
			r = tmi_run_next(&tmi, 1);
		}
		else {
			r = tmi_run_next(&tmi, 0);	
		}
	}

	printf("%d\n", r);

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	clear_tmi(&tmi);
	r = init_tmi(&tmi, 20000, argv[1]);
	printf("init %d\n", r);

	d = &tmi.mt.memory_tape;
	r = tmi_run_next(&tmi, 0);
	while((r > -1) || (r < -9)){
		printf("tmi_run_next %d\n", r);
		d = &tmi.mt.memory_tape;
		while((d != NULL) && (d->value != ' ')) {
			printf("%c", (char)d->value);
			d = d->next;
		}
		printf("\n");
		if(r < -9) {
			r = tmi_run_next(&tmi, 1);
		}
		else {
			r = tmi_run_next(&tmi, 0);	
		}
	}

	printf("%d\n", r);

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	clear_tmi(&tmi);
	r = init_tmi(&tmi, 20000, argv[1]);
	printf("init %d\n", r);

	d = &tmi.mt.memory_tape;
	r = tmi_run_next(&tmi, 0);
	while((r > -1) || (r < -9)){
		printf("tmi_run_next %d\n", r);
		d = &tmi.mt.memory_tape;
		while((d != NULL) && (d->value != ' ')) {
			printf("%c", (char)d->value);
			d = d->next;
		}
		printf("\n");
		if(r < -9) {
			r = tmi_run_next(&tmi, 1);
		}
		else {
			r = tmi_run_next(&tmi, 0);	
		}
	}

	printf("%d\n", r);

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	clear_tmi(&tmi);
	r = init_tmi(&tmi, 20000, argv[1]);
	printf("init %d\n", r);

	d = &tmi.mt.memory_tape;
	r = tmi_run_next(&tmi, 0);
	while((r > -1) || (r < -9)){
		printf("tmi_run_next %d\n", r);
		d = &tmi.mt.memory_tape;
		while((d != NULL) && (d->value != ' ')) {
			printf("%c", (char)d->value);
			d = d->next;
		}
		printf("\n");
		if(r < -9) {
			r = tmi_run_next(&tmi, 1);
		}
		else {
			r = tmi_run_next(&tmi, 0);	
		}
	}

	printf("%d\n", r);

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");

	r = tmi_run_prev(&tmi);
	printf("run prev %d\n", r);

	d = &tmi.mt.memory_tape;
	while((d != NULL) && (d->value != ' ')) {
		printf("%c", (char)d->value);
		d = d->next;
	}
	printf("\n");
	
	return 0;
}