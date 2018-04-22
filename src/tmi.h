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
int tmi_run_next(struct TMI* tmi, int flag);
#endif