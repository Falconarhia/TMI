#ifndef TMI_H
#define TMI_H

#include <stdio.h>
#include "mt.h"
#include "double_linked_list.h"
#include "parcer.h"

#define SIZE_STR 100

struct TMI {
	struct MT mt;
	struct DLL_Node instruction;
	struct DLL_Node breakpoint;
};

int init_tmi(struct TMI* tmi, size_t len_mtape, const char* filename);
void clear_tmi(struct TMI* tmi);
#endif