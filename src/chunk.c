#include <stdlib.h>

#include "chunk.h"
#include "lineInfo.h"
#include "memory.h"
#include "vm.h"

void initChunk(Chunk* chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	initLineInfo(&chunk->lineInfo);
	initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	freeLineInfo(&chunk->lineInfo);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
	if (chunk->capacity < chunk->count + 1) {
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
	}

	chunk->code[chunk->count] = byte;
	writeLineInfo(&chunk->lineInfo, line);
	chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
	push(value);
	writeValueArray(&chunk->constants, value);
	pop();
	return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int chunkIndex) {
	int i = 0;
	int chunkCount = 0;
	while (chunkCount <= chunkIndex) {
		chunkCount += (chunk->lineInfo).repeats[i];
		i++;
	}
	return (chunk->lineInfo).lines[i-1];
}

