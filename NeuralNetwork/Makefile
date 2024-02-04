# Makefile

CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -fsanitize=address -O3 -g
LDFLAGS = -fsanitize=address
LDLIBS =  `pkg-config --libs sdl SDL_image ` -lm
BIN = main

all : main

main : neuralnetwork.o pixel_operations.o imageToNeural.o 
main.o : mnist_parse.h neuralnetwork.h

clean :
	${RM} *.o
	${RM} *.d
	${RM} $(BIN)

# END
