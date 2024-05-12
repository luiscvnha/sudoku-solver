#include "solve.h"
#include "ext.h"
#include "stack.h"


typedef enum state {
    FULL,
    DEAD_END,
    NEW_GUESS
} State;


static uint8_t get_solution(const bool available[], uint8_t* out_solution) {
    uint8_t num_available = 0;

    for (uint8_t i = 0; i < GRID_SIDE; ++i) {
        if (available[i]) {
            ++num_available;
            *out_solution = i + 1;
        }
    }

    return num_available;
}


static void get_available(Grid grid, uint8_t i, uint8_t j, bool out_available[]) {
    uint8_t x, y;

    for (x = 0; x < GRID_SIDE; ++x) {
        out_available[x] = true;
    }

    // check line and column
    for (x = 0; x < GRID_SIDE; ++x) {
        if (grid_get(grid, i, x) != GRID_EMPTY) {
            out_available[grid_get(grid, i, x) - 1] = false;
        }
        if (grid_get(grid, x, j) != GRID_EMPTY) {
            out_available[grid_get(grid, x, j) - 1] = false;
        }
    }

    // check 3x3 square
    x = i - i % 3;
    y = j - j % 3;
    for (uint8_t a = 0; a < 3; ++a) {
        for (uint8_t b = 0; b < 3; ++b) {
            if (grid_get(grid, x+a, y+b) != GRID_EMPTY) {
                out_available[grid_get(grid, x+a, y+b) - 1] = false;
            }
        }
    }
}


static void undo(Grid grid, Stack stack) {
    uint8_t i, j;
    bool guessed;

    do {
        if (!stack_pop(stack, &i, &j, &guessed)) break;
        grid_set(grid, i, j, GRID_EMPTY);
    } while (!guessed);
}


static State fill(Grid grid, Stack stack, uint8_t* out_i, uint8_t* out_j) {
    uint8_t i, j, solution, num_available;
    bool stop = false;
    bool available[GRID_SIDE];

    while (!stop) {
        stop = true;
        for (i = 0; i < GRID_SIDE; ++i) {
            for (j = 0; j < GRID_SIDE; ++j) {
                if (grid_get(grid, i, j) == GRID_EMPTY) {
                    get_available(grid, i, j, available);
                    num_available = get_solution(available, &solution);
                    if (num_available == 0) {
                        return DEAD_END;
                    }
                    else if (num_available == 1) {
                        grid_set(grid, i, j, solution);
                        stack_push(stack, i, j, false);
                        stop = false;
                    }
                }
            }
        }
    }

    State state = FULL;
    uint8_t count = GRID_SIDE + 1;

    for (i = 0; i < GRID_SIDE; ++i) {
        for (j = 0; j < GRID_SIDE; ++j) {
            if (grid_get(grid, i, j) == GRID_EMPTY) {
                state = NEW_GUESS;
                get_available(grid, i, j, available);
                num_available = get_solution(available, &solution);
                if (num_available < count) {
                    *out_i = i;
                    *out_j = j;
                    count = num_available;
                }
            }
        }
    }

    return state;
}


static uint8_t solve_grid_rec(Grid grid, Stack stack, uint8_t i, uint8_t j, Grid* out_grid) {
    uint8_t x, i2, j2;
    uint8_t num_solutions = 0;
    State state;
    bool available[GRID_SIDE];

    get_available(grid, i, j, available);
    for (x = 0; x < GRID_SIDE && num_solutions < 2; ++x) {
        if (available[x]) {
            grid_set(grid, i, j, x+1);
            stack_push(stack, i, j, true);
            state = fill(grid, stack, &i2, &j2);
            switch (state) {
                case FULL:
                    if (++num_solutions == 1) {
                        *out_grid = grid_clone(grid);
                    }
                    break;

                case DEAD_END:
                    break;

                case NEW_GUESS:
                    num_solutions += solve_grid_rec(grid, stack, i2, j2, out_grid);
                    break;
            }
            undo(grid, stack);
        }
    }

    return num_solutions;
}


uint8_t solve_grid(ReadonlyGrid in_grid, Grid* out_grid) {
    uint8_t i, j, num_solutions;
    State state;
    Stack stack = stack_new();
    Grid grid = grid_clone(in_grid);

    state = fill(grid, stack, &i, &j);

    switch (state) {
        case FULL:
            *out_grid = grid_clone(grid);
            num_solutions = 1;
            break;

        case DEAD_END:
            num_solutions = 0;
            break;

        case NEW_GUESS:
            num_solutions = solve_grid_rec(grid, stack, i, j, out_grid);
            break;
    }

    stack_destroy(&stack);
    grid_destroy(&grid);

    return num_solutions;
}
