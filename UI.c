#include "UI.h"

void print_info() {
    puts("(i) Spaces and 0's count as empty\n");
}

void input_line(char in[]) {
    BYTE j;

    if (scanf("%[^\n]s", in) == 0) in[0] = '\0';
    getchar();          //flush stdin
    in[SIZE] = '\0';
    for (j = strlen(in); j < SIZE; ++j)
        in[j] = '0';
}

void input(GRID grid_in, GRID grid_test) {
    BYTE i, j;
    char in[2*SIZE+1];

    puts("Input:");
    puts("   123456789\n");
    for (i = 0; i < SIZE; ++i) {
        printf("%d  ", i+1);
        input_line(in);
        for (j = 0; j < SIZE; ++j) {
            if (in[j] == ' ' || in[j] == '0') {
                grid_in[i][j] = EMPTY;
                grid_test[i][j] = EMPTY;
            } else if (in[j] >= '1' && in[j] <= '9') {
                grid_in[i][j] = in[j] - '0';
                grid_test[i][j] = in[j] - '0';
            } else {
                j = SIZE;
                --i;
            }
        }
    }
}

void print_sol(GRID grid_in, GRID grid_out) {
    BYTE i, j;

    puts("Grid:                     Solution:");
    for (i = 0; i < SIZE; ++i) {
        if (i % 3 == 0) puts("+---+---+---+             +---+---+---+");
        for (j = 0; j < SIZE; ++j) {
            if (j % 3 == 0) putchar('|');
            if (grid_in[i][j] == EMPTY) putchar(' ');
            else printf("%d", grid_in[i][j]);
        }
        printf("|             ");
        for (j = 0; j < SIZE; ++j) {
            if (j % 3 == 0) putchar('|');
            if (grid_out[i][j] == EMPTY) putchar(' ');
            else printf("%d", grid_out[i][j]);
        }
        puts("|");
    }
    puts("+---+---+---+             +---+---+---+");
}

void print_err(GRID grid, BYTE error) {
    BYTE i, j;

    puts("Grid:");
    for (i = 0; i < SIZE; ++i) {
        if (i % 3 == 0) puts("+---+---+---+");
        for (j = 0; j < SIZE; ++j) {
            if (j % 3 == 0) putchar('|');
            if (grid[i][j] == EMPTY) putchar(' ');
            else printf("%d", grid[i][j]);
        }
        putchar('|');
        if (i == 4) {
            if (error == 0) printf("             ERROR: Grid has no solution!");
            else if (error == OUT_OF_MEMORY) printf("             ERROR: Out of memory!");
            else printf("             ERROR: Grid has multiple solutions!");
        }
        putchar('\n');
    }
    puts("+---+---+---+");
}
