IDIR := inc
SDIR := src
ODIR := obj

CC := gcc
CFLAGS := -Wall -Wextra -O2 -std=c17 -I${IDIR}

DEPS := ${wildcard ${IDIR}/*.h}
SRCS := ${wildcard ${SDIR}/*.c}
OBJS := ${subst ${SDIR}/,${ODIR}/,${SRCS}}
OBJS := ${subst .c,.o,${OBJS}}

BIN := sudokusolver


.DEFAULT_GOAL := ${BIN}

.PHONY: clean


${ODIR}/%.o: ${SDIR}/%.c ${DEPS}
	${CC} ${CFLAGS} -c -o $@ $<

${BIN}: ${OBJS}
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm -f ${ODIR}/*.o ${BIN}
