#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,
	OP_NIL,
	OP_TRUE,
	OP_FALSE,
	OP_POP,
	OP_GET_LOCAL,
	OP_SET_LOCAL,
	OP_GET_GLOBAL,
	OP_DEFINE_GLOBAL,
	OP_SET_GLOBAL,
	OP_GET_UPVALUE,
	OP_SET_UPVALUE,
	OP_GET_PROPERTY,
	OP_SET_PROPERTY,
	OP_GET_SUPER,
	OP_EQUAL,
	OP_GREATER,
	OP_LESS,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_NOT,
	OP_NEGATE,
	OP_PRINT,
	OP_JUMP,
	OP_JUMP_IF_FALSE,
	OP_LOOP,
	OP_CALL,
	OP_INVOKE,
	OP_SUPER_INVOKE,
	OP_CLOSURE,
	OP_RETURN,
	OP_CLOSE_UPVALUE,
	OP_CLASS,
	OP_INHERIT,
	OP_METHOD
} OpCode;

//////////       My Solution to Challenge 1 from Chapter 14        /////////
// Encoding the lines for chunks using something like run-length encoding //
//   to improve on Nystrom's given encoding of line information that he   //
//             refers to as "hilariously wasteful of memory".             //
////////////////////////////////////////////////////////////////////////////
typedef struct {
	int size;
	int capacity;
	int* lines;
	int* repeats;
} LineInfo;

typedef struct {
	int count;
	int capacity;
	uint8_t* code;
	LineInfo lineInfo;
	ValueArray constants;	
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void initLineInfo(LineInfo* lineInfo);
void writeLineInfo(LineInfo* lineInfo, int line);
void freeLineInfo(LineInfo* lineInfo);
int addConstant(Chunk* chunk, Value value);
int getLine(Chunk* chunk, int chunkIndex);

#endif