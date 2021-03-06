#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include "instruction_list.h"

int is_printed_char(char c);
int parser_instruction(struct Instruction* instruction, const char* str);
#endif