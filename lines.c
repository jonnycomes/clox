#include <stdlib.h>

#include "memory.h"
#include "lines.h"

void initLines(Lines* lines) {
	lines->size = 0;
	lines->lines = NULL;
	lines->repeats = NULL;
}

void writeLines(Lines* lines, int line) {
	if (lines->size > 0 && line == lines->lines[lines->size - 1]) {
		lines->repeats[lines->size - 1]++;
	} else {
		lines->lines = GROW_ARRAY(int, lines->lines, lines->size, lines->size + 1);
		lines->repeats = GROW_ARRAY(int, lines->repeats, lines->size, lines->size + 1);
		lines->lines[lines->size] = line;
		lines->repeats[lines->size] = 1;
		lines->size++;
	}
}

void freeLines(Lines* lines) {
	FREE_ARRAY(int, lines->lines, lines->size);
	FREE_ARRAY(int, lines->repeats, lines->size);
	initLines(lines);
}

int getLine(Lines* lines, int chunkIndex) {
	int i = 0;
	int chunkCount = 0;
	while (chunkCount < chunkIndex + 1) {
		chunkCount += lines->repeats[i];
		i++;
	}
	return lines->lines[i-1];
}
