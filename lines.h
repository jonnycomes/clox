//////////       My Solution to Challenge 1 from Chapter 14        /////////
// Encoding the lines for chunks using something like run-length encoding //
//   to improve on Nystrom's given encoding of line information that he   //
//             refers to as "hilariously wasteful of memory".             //
////////////////////////////////////////////////////////////////////////////

#ifndef clox_lines_h
#define clox_lines_h

#include "common.h"

typedef struct {
	int size;
	int* lines;
	int* repeats;
} Lines;

void initLines(Lines* lines);
void writeLines(Lines* lines, int line);
void freeLines(Lines* lines);
int getLine(Lines* lines, int chunkIndex);

#endif