#ifndef TMI_H
#define TMI_H

#include <stdio.h>
#include "mt.h"
#include "double_linked_list.h"
#include "parser.h"

#define SIZE_STR 100

struct TMI {
	struct MT mt;
	struct DLL_Node instruction;
	struct DLL_Node breakpoint;
};

int init_tmi(struct TMI* tmi, size_t len_mtape, const char* filename);
void clear_tmi(struct TMI* tmi);
int tmi_run_next(struct TMI* tmi, int flag);
int tmi_run_prev(struct TMI* tmi);
#endif
