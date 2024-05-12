#include "ext.h"
#include "grid.h"
#include "stack.h"
#include "view.h"
#include "solve.h"

#include <string.h>


int main(int argc, char* argv[]) {
    view_setup();

    bool interactive_mode;
    if (argc == 1) {
        interactive_mode = false;
    }
    else if (argc == 2 && strcmp(argv[1], "-i") == 0) {
        interactive_mode = true;
    }
    else {
        view_usage(argv[0]);
        return EXIT_FAILURE;
    }

    Grid input_grid = NULL;
    bool successful_input = view_input_grid(interactive_mode, &input_grid);
    if (!successful_input) {
        return EXIT_FAILURE;
    }

    Grid output_grid = NULL;
    uint8_t solutions = solve_grid(input_grid, &output_grid);
    switch (solutions) {
        case 0:
            view_no_solutions_error();
            break;

        case 1:
            view_output_grid(input_grid, output_grid);
            break;

        default:
            view_multiple_solutions_error();
            break;
    }

    grid_destroy(&input_grid);
    grid_destroy(&output_grid);

    return EXIT_SUCCESS;
}
