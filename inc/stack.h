#ifndef __stack_h__
#define __stack_h__

/*==================== Imports ====================*/

#include <inttypes.h>
#include <stdbool.h>


/*=================== Data Types ===================*/

typedef struct stack_entry* StackEntry;


typedef StackEntry* Stack;


/*=================== Functions ===================*/

Stack stack_new(void);


void stack_push(Stack stack, uint8_t i, uint8_t j, bool guessed);


bool stack_pop(Stack stack, uint8_t* out_i, uint8_t* out_j, bool* out_guessed);


void stack_destroy(Stack* stack_ptr);


/*=================================================*/

#endif
