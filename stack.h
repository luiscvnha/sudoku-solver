#ifndef ___STACK_H___
#define ___STACK_H___

#include <stdlib.h>
#include "general.h"

#define FILLED      0
#define GUESSED     1

typedef struct entry {
    BYTE i;
    BYTE j;
    BYTE way;			// FILLED || GUESSED
    struct entry *next;
} *STACK;

BYTE push(STACK *, BYTE, BYTE, BYTE);

BYTE pop(STACK *, BYTE *, BYTE *, BYTE *);

#endif
