#include "view.h"
#include "ext.h"

#include <stdio.h>
#include <string.h>


#define ANSI_RESET_ALL          "\x1b[0m"

#define ANSI_COLOR_GREEN        "\x1b[32m"

#define ANSI_STYLE_BOLD         "\x1b[1m"


static bool get_line(char out_line[]) {
    int c;
    uint8_t i = 0;
    bool is_valid = true;

    while ((c = getchar()) != EOF && c != '\n') {
        if ((c != ' ' && (c < '0' || c > '9')) || i >= GRID_SIDE) {
            is_valid = false;
            break;
        }

        out_line[i++] = (char) c;
    }

    if (is_valid) {
        while (i < GRID_SIDE) {
            out_line[i++] = '0';
        }
    }

    if (c != EOF && c != '\n') {
        while ((c = getchar()) != EOF && c != '\n');
    }

    return is_valid;
}


void view_setup(void) {
    setbuf(stdout, NULL);
}


void view_usage(const char* progam_name) {
    printf("Usage:\n");
    printf("    %s -i\n", progam_name);
    printf("    %s < input-file.txt\n", progam_name);
}


void view_no_solutions_error(void) {
    puts("No solutions found.");
}


void view_multiple_solutions_error(void) {
    puts("Multiple solutions found.");
}


bool view_input_grid(bool interactive_mode, Grid* out_grid) {
    Grid grid = grid_new();
    char line[GRID_SIDE];

    if (interactive_mode) {
        puts(ANSI_STYLE_BOLD "   123456789" ANSI_RESET_ALL);
        puts(ANSI_STYLE_BOLD "  +---------" ANSI_RESET_ALL);
    }

    for (uint8_t i = 0; i < GRID_SIDE;) {
        if (interactive_mode) {
            printf(ANSI_STYLE_BOLD "%" PRIu8 " |" ANSI_RESET_ALL, i+1);
        }

        if (get_line(line)) {
            for (uint8_t j = 0; j < GRID_SIDE; ++j) {
                uint8_t val = line[j] == ' ' ? GRID_EMPTY : char_to_num(line[j]);
                grid_set(grid, i, j, val);
            }
            ++i;
        } else {
            if (interactive_mode) {
                // continue
            } else {
                puts("Invalid input.");
                grid_destroy(&grid);
                return false;
            }
        }
    }

    if (interactive_mode) {
        putchar('\n');
    }

    *out_grid = grid;
    return true;
}


void view_output_grid(ReadonlyGrid input_grid, ReadonlyGrid output_grid) {
    printf(ANSI_STYLE_BOLD "+-----------------------+" ANSI_RESET_ALL "\n");

    for (uint8_t i = 0; i < GRID_SIDE; ++i) {
        printf(ANSI_STYLE_BOLD "|" ANSI_RESET_ALL);

        for (uint8_t j = 0; j < GRID_SIDE; ++j) {
            printf(" ");

            uint8_t val = grid_get(output_grid, i, j);
            if (val >= 1 && val <= 9) {
                if (grid_get(input_grid, i, j) == GRID_EMPTY) {
                    printf(ANSI_COLOR_GREEN "%" PRIu8 ANSI_RESET_ALL, val);
                } else {
                    printf("%" PRIu8, val);
                }
            } else {
                printf(" ");
            }

            if (j == 2 || j == 5) {
                printf(" " ANSI_STYLE_BOLD "|" ANSI_RESET_ALL);
            }
        }

        printf(" " ANSI_STYLE_BOLD "|" ANSI_RESET_ALL "\n");

        if (i == 2 || i == 5) {
            printf(ANSI_STYLE_BOLD "|-------+-------+-------|" ANSI_RESET_ALL "\n");
        }
    }

    printf(ANSI_STYLE_BOLD "+-----------------------+" ANSI_RESET_ALL "\n");
}
