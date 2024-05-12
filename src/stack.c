#include "stack.h"
#include "ext.h"

#include <stdlib.h>


struct stack_entry {
    uint8_t i;
    uint8_t j;
    bool guessed;
    struct stack_entry* next;
};


Stack stack_new(void) {
    return (Stack) calloc_t(StackEntry);
}


void stack_push(Stack stack, uint8_t i, uint8_t j, bool guessed) {
    StackEntry new_entry = (StackEntry) malloc_t(struct stack_entry);

    new_entry->i = i;
    new_entry->j = j;
    new_entry->guessed = guessed;
    new_entry->next = *stack;

    *stack = new_entry;
}


bool stack_pop(Stack stack, uint8_t* out_i, uint8_t* out_j, bool* out_guessed) {
    StackEntry first_entry = *stack;
    if (first_entry == NULL) return false;

    *out_i = first_entry->i;
    *out_j = first_entry->j;
    *out_guessed = first_entry->guessed;

    *stack = first_entry->next;
    free(first_entry);

    return true;
}


void stack_destroy(Stack* stack_ptr) {
    Stack stack = *stack_ptr;
    if (stack == NULL) return;

    StackEntry current_entry = *stack;
    while (current_entry != NULL) {
        StackEntry next_entry = current_entry->next;
        free(current_entry);
        current_entry = next_entry;
    }

    free(stack);
    *stack_ptr = NULL;
}
