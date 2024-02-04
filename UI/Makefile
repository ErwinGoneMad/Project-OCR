# Makefile

CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = `pkg-config --cflags gtk+-3.0` -O3 -g
LDFLAGS =
LDLIBS = `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl SDL_image SDL_ttf SDL_gfx` -lm
BIN = user_interface

all : user_interface

user_interface : ../Image/preprocessing.o  ../Image/pixel_operations.o ../Image/display.o ../Image/remove_color.o ../Image/gaussian_filter.o ../Image/sobel_filter.o ../Image/hough_transform.o ../Image/Splitting.o ../Image/reconstruct.o ../Solver/grid_read.o

clean :
	${RM} *.o
	${RM} *.d
	${RM} *#*
	${RM} *~
	${RM} *.bmp
	${RM} $(BIN)

# END
