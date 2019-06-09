#ifndef solve_h
#define solve_h


#include "general.h"
#include "stack.h"


#define FULL				0
#define DEAD_END			1
#define NEW_GUESS			2


Byte check_used(Byte used[], Byte *sol);

void get_used(Byte used[], Grid grid, Byte i, Byte j);

Byte fill(Grid grid, Stack *stack, Byte *ri, Byte *rj);

void undo(Grid grid, Stack *pstack);

void copy_grid(Grid grid1, Grid grid2);

Byte solve_aux(Grid grid_test, Grid **grid_out, Stack *pstack, Byte i, Byte j);

Byte solve(Grid *grid_test, Grid **grid_out);


#endif
