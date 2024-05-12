#ifndef __grid_h__
#define __grid_h__

/*==================== Imports ====================*/

#include <inttypes.h>


/*=================== Constants ===================*/

// grid's dimensions
#define GRID_SIDE       9


// empty field value
#define GRID_EMPTY      ((uint8_t) 0)


/*=================== Data Types ===================*/

typedef uint8_t* Grid;


typedef const uint8_t* ReadonlyGrid;


/*=================== Functions ===================*/

Grid grid_new(void);


uint8_t grid_get(ReadonlyGrid grid, uint8_t i, uint8_t j);


void grid_set(Grid grid, uint8_t i, uint8_t j, uint8_t value);


Grid grid_clone(ReadonlyGrid grid);


void grid_destroy(Grid* grid_ptr);


/*=================================================*/

#endif
