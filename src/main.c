#include <stdio.h>
#include "../inc/general.h"
#include "../inc/UI.h"
#include "../inc/solve.h"


int main() {
	Byte s;
	Grid grid_in, grid_test, *grid_out = NULL;

	setbuf(stdout, NULL);

	print_info();

	input(grid_in, grid_test);

	putchar('\n');

	if ((s = solve(&grid_test, &grid_out)) == 1)
		print_sol(grid_in, *grid_out);
	else
		print_err(grid_in, s);

	return 0;
}
