#ifndef ___SOLVE_H___
#define ___SOLVE_H___

#include "general.h"
#include "stack.h"

#define FULL            0
#define DEAD_END        1
#define NEW_GUESS       2

BYTE check_used(BYTE [], BYTE *);

void get_used(BYTE [], GRID, BYTE, BYTE);

BYTE fill(GRID, STACK *, BYTE *, BYTE *);

void undo(GRID, STACK *);

void copy_grid(GRID, GRID);

BYTE solve_aux(GRID, GRID **, STACK *, BYTE, BYTE);

BYTE solve(GRID *, GRID **);

#endif
