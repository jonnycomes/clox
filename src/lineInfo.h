//////////       My Solution to Challenge 1 from Chapter 14        /////////
// Encoding the lines for chunks using something like run-length encoding //
//   to improve on Nystrom's given encoding of line information that he   //
//             refers to as "hilariously wasteful of memory".             //
////////////////////////////////////////////////////////////////////////////

#ifndef clox_line_info_h
#define clox_line_info_h

#include "common.h"

typedef struct {
	int size;
	int capacity;
	int* lines;
	int* repeats;
} LineInfo;

void initLineInfo(LineInfo* lineInfo);
void writeLineInfo(LineInfo* lineInfo, int line);
void freeLineInfo(LineInfo* lineInfo);

#endif