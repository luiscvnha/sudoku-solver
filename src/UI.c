#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../inc/UI.h"


static void flush() {
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

static Bool input_line(char in[]) {
	int bytes_read = read(STDIN_FILENO, in, SIZE);
	if (bytes_read <= 0) {putchar('\n'); return false;}

	if (bytes_read == SIZE && in[SIZE-1] != '\n') flush();

	if (in[bytes_read-1] == '\n') --bytes_read;

	for (; bytes_read < SIZE; ++bytes_read)
		in[bytes_read] = '0';

	return true;
}

void print_info() {
	puts("(i) Spaces and 0's count as empty\n");
}

void input(Grid grid_in, Grid grid_test) {
	char in[SIZE];

	puts("Input:");
	puts("   123456789\n");
	for (Byte i = 0; i < SIZE;) {
		printf("%d  ", i+1);
		if (input_line(in)) {
			for (Byte j = 0; j < SIZE; ++j)
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
			++i;
		}
	}
}

void print_sol(Grid grid_in, Grid grid_out) {
    Byte i, j;

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

void print_err(Grid grid, Byte error) {
    Byte i, j;

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
