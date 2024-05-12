#include "grid.h"
#include "ext.h"

#include <string.h>


// grid's total size in bytes
#define GRID_SIZE_BYTES         sizeof_ct(GRID_SIDE * GRID_SIDE, uint8_t)


Grid grid_new(void) {
    return (Grid) calloc_s(GRID_SIZE_BYTES);
}


uint8_t grid_get(ReadonlyGrid const grid, uint8_t i, uint8_t j) {
    return grid[i*GRID_SIDE + j];
}


void grid_set(Grid grid, uint8_t i, uint8_t j, uint8_t value) {
    grid[i*GRID_SIDE + j] = value;
}


Grid grid_clone(ReadonlyGrid grid) {
    Grid r = (Grid) malloc_s(GRID_SIZE_BYTES);
    memcpy(r, grid, GRID_SIZE_BYTES);
    return r;
}


void grid_destroy(Grid* grid_ptr) {
    Grid grid = *grid_ptr;
    if (grid == NULL) return;

    free(grid);
    *grid_ptr = NULL;
}
