INCDIR = inc
SRCDIR = src
OBJDIR = obj

CC = gcc
EXE = sudokusolver
CFLAGS = -Wall -Wextra -pedantic -march=native -O3 -pipe

_DEPS = general.h UI.h solve.h stack.h
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

_OBJ = UI.o solve.o stack.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))


program: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(SRCDIR)/main.c $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR)/*.o
