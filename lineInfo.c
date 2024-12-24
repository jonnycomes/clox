#include <stdlib.h>

#include "memory.h"
#include "lineInfo.h"

void initLineInfo(LineInfo* lineInfo) {
	lineInfo->capacity = 0;
	lineInfo->size = 0;
	lineInfo->lines = NULL;
	lineInfo->repeats = NULL;
}

void writeLineInfo(LineInfo* lineInfo, int line) {
	if (lineInfo->size > 0 && line == lineInfo->lines[lineInfo->size - 1]) {
		lineInfo->repeats[lineInfo->size - 1]++;
	} else {
		if (lineInfo->capacity < lineInfo->size + 1) {
			int oldCapacity = lineInfo->capacity;
			lineInfo->capacity = GROW_CAPACITY(oldCapacity);
			lineInfo->lines = GROW_ARRAY(int, lineInfo->lines, oldCapacity, lineInfo->capacity);
			lineInfo->repeats = GROW_ARRAY(int, lineInfo->repeats, oldCapacity, lineInfo->capacity);
		} 
		lineInfo->lines[lineInfo->size] = line;
		lineInfo->repeats[lineInfo->size] = 1;
		lineInfo->size++;
	}
}

void freeLineInfo(LineInfo* lineInfo) {
	FREE_ARRAY(int, lineInfo->lines, lineInfo->size);
	FREE_ARRAY(int, lineInfo->repeats, lineInfo->size);
	initLineInfo(lineInfo);
}

int getLine(LineInfo* lineInfo, int chunkIndex) {
	int i = 0;
	int chunkCount = 0;
	while (chunkCount <= chunkIndex) {
		chunkCount += lineInfo->repeats[i];
		i++;
	}
	return lineInfo->lines[i-1];
}
