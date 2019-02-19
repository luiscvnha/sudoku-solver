CC = gcc
CFLAGS = -Wall -Wextra -O2
EXE = SudokuSolver
OBJS = main.o UI.o solve.o stack.o

compile: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

clean:
	rm -rf *.o
