CC=gcc
CFLAGS= `sdl2-config --cflags --libs`
DEPS = window.h renderer.h
OBJ = window.c main.c renderer.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

AlphaDice: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)