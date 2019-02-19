CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -O2
EXECUTAVEL=SudokuSolver
OBJS=main.o UI.o solve.o stack.o

compile: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXECUTAVEL) $(OBJS)

clean:
	rm -rf *.o

