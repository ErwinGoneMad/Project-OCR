# Simple Makefile

# Compilers vars
CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS=

main: main.o grid_write.o grid_read.o sudoku_solver.o

main.o: grid_write.h grid_read.h sudoku_solver.h

clean:
	rm -f *.o
	rm -f *.d
	rm -f *.result
	rm -f ${DEP}
	rm -f ${PRG}

# END Makefile