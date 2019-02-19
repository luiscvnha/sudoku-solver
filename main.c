#include "general.h"
#include "UI.h"
#include "solve.h"

int main() {
    BYTE s;
    GRID grid_in, grid_test, *grid_out = NULL;

    print_info();
    
    input(grid_in, grid_test);

    putchar('\n');

    if ((s = solve(&grid_test, &grid_out)) == 1)
        print_sol(grid_in, *grid_out);
    else
        print_err(grid_in, s);

    return 0;
}
