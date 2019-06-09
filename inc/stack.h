#ifndef stack_h
#define stack_h


#include "general.h"


#define FILLED			0
#define GUESSED			1


typedef struct entry {
	Byte i;
	Byte j;
	Byte way;				// FILLED || GUESSED
	struct entry* next;
} *Stack;


Byte push(Stack *pstack, Byte i, Byte j, Byte way);

Byte pop(Stack *pstack, Byte *i, Byte *j, Byte *way);


#endif
