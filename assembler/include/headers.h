#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 128

void assemble(char **text, int linecount, FILE *outfile);
void disassemble(char **text, int linecount, FILE *outfile);
