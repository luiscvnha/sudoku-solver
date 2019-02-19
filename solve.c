#include "solve.h"

//  output: number of possibilities for that position
//  sol:    solution if there's only one possibility
BYTE check_used(BYTE used[], BYTE *sol) {
    BYTE i, r = 0;

    for (i = 0; i < SIZE; ++i)
        if (used[i] == FALSE) {
            ++r;
            *sol = i + 1;
        }

    return r;
}

void get_used(BYTE used[], GRID grid, BYTE i, BYTE j) {
    BYTE x, y, m, n;

    // initialize array with 0's
    for (x = 0; x < SIZE; ++x)
        used[x] = FALSE;
    // check line and column
    for (x = 0; x < SIZE; ++x) {
        if (grid[i][x] != EMPTY)
            used[grid[i][x] - 1] = TRUE;
        if (grid[x][j] != EMPTY)
            used[grid[x][j] - 1] = TRUE;
    }
    // check 3x3 square
    x = i - i % 3;
    y = j - j % 3;
    for (m = 0; m < 3; ++m)
        for (n = 0; n < 3; ++n)
            if (grid[x + m][y + n] != EMPTY)
                used[grid[x + m][y + n] - 1] = TRUE;
}

//  0:      grid's full             FULL
//  1:      no solution             DEAD_END
//  2:      guess new position      NEW_GUESS
//  255:    out of memory           OUT_OF_MEMORY
BYTE fill(GRID grid, STACK *stack, BYTE *ri, BYTE *rj) {
    BYTE i, j, sol, num_poss, stop = FALSE, r, count = SIZE, used[SIZE];

    while (!stop) {
        stop = TRUE;
        r = FULL;
        for (i = 0; i < SIZE; ++i)
            for (j = 0; j < SIZE; ++j)
                if (grid[i][j] == EMPTY) {
                    get_used(used, grid, i, j);
                    if ((num_poss = check_used(used, &sol)) == 0)
                        return DEAD_END;
                    else if (num_poss == 1) {
                        grid[i][j] = sol;
                        if (stack != NULL && push(stack, i, j, FILLED) == 1)
                            return OUT_OF_MEMORY;
                        stop = FALSE;
                    } else if (r == FULL || count > num_poss) {     // for the last iteration
                        r = NEW_GUESS;
                        *ri = i;
                        *rj = j;
                        count = num_poss;
                    }
                }
    }

    return r;
}

void undo(GRID grid, STACK *pstack) {
    BYTE i, j, way;

    do {
        if (pop(pstack, &i, &j, &way) == 1) break;
        grid[i][j] = EMPTY;
    } while (way == FILLED);
}

void copy_grid(GRID grid1, GRID grid2) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            grid2[i][j] = grid1[i][j];
}

//  0:      no solutions found
//  1:      only one solution found
//  2+:     more than one solution found
//  255:    out of memory                   OUT_OF_MEMORY
BYTE solve_aux(GRID grid_test, GRID **grid_out, STACK *pstack, BYTE i, BYTE j) {
    static BYTE num_sol = 0;
    BYTE index, x, used[SIZE], i2, j2;

    get_used(used, grid_test, i, j);
    for (x = 0; x < SIZE && num_sol < 2; ++x)
        if (used[x] == FALSE) {
            grid_test[i][j] = x+1;
            if (push(pstack, i, j, GUESSED) == 1)
                return OUT_OF_MEMORY;
            index = fill(grid_test, pstack, &i2, &j2);
            switch (index) {
                case FULL:  if (++num_sol == 1) {
                                if ((*grid_out = (GRID *) malloc(sizeof(GRID))) == NULL)
                                    return OUT_OF_MEMORY;
                                copy_grid(grid_test, **grid_out);
                                undo(grid_test, pstack);
                            } break;
                case DEAD_END:  undo(grid_test, pstack); break;
                case OUT_OF_MEMORY: return OUT_OF_MEMORY;
                case NEW_GUESS: if (solve_aux(grid_test, grid_out, pstack, i2, j2) == OUT_OF_MEMORY)
                                    return OUT_OF_MEMORY;
            }
        }

    return num_sol;
}

//  0:      no solutions found
//  1:      only one solution found
//  2+:     more than one solution found
//  255:    out of memory                   OUT_OF_MEMORY
BYTE solve(GRID *grid_test, GRID **grid_out) {
    BYTE index, i, j, r;
    STACK stack = NULL;

    index = fill(*grid_test, NULL, &i, &j);
    switch (index) {
        case FULL:  *grid_out = grid_test;
                    r = 1;
                    break;
        case DEAD_END:  r = 0;
                        break;
        case NEW_GUESS: r = solve_aux(*grid_test, grid_out, &stack, i, j);
                        break;
        default:    r = OUT_OF_MEMORY;
    }

    return r;
}
