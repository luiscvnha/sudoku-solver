#ifndef __view_h__
#define __view_h__

/*==================== Imports ====================*/

#include "grid.h"

#include <stdbool.h>


/*=================== Functions ===================*/

void view_setup(void);


void view_usage(const char* progam_name);


void view_no_solutions_error(void);


void view_multiple_solutions_error(void);


bool view_input_grid(bool interactive_mode, Grid* out_grid);


void view_output_grid(ReadonlyGrid input_grid, ReadonlyGrid output_grid);


/*=================================================*/

#endif
