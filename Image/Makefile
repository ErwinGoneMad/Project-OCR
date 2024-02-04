# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS= -fsanitize=address -Wl,-V
LDLIBS= `pkg-config --libs sdl SDL_image` -lm
BIN = reconstruct

all : reconstruct

reconstruct : ../Solver/grid_read.o display.o

clean:
	${RM} *.o
	${RM} *.d
	${RM} *~
	${RM} $(BIN)

# END
