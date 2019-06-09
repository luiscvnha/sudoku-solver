#include <stdlib.h>
#include "../inc/stack.h"


//  0: success
//  1: out of memory
Byte push(Stack *pstack, Byte i, Byte j, Byte way) {
    struct entry* new;

    new = (struct entry*) malloc(sizeof(struct entry));
    if (new == NULL) return 1;

    new->i = i;
    new->j = j;
    new->way = way;
    new->next = *pstack;
    *pstack = new;

    return 0;
}

//  0: success
//  1: empty stack
Byte pop(Stack *pstack, Byte *i, Byte *j, Byte *way) {
    Stack stack = *pstack;

    if (stack == NULL) return 1;

    *i = stack->i;
    *j = stack->j;
    *way = stack->way;
    *pstack = stack->next;
    free(stack);

    return 0;
}
