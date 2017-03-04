CC=gcc
CFLAGS= `sdl2-config --cflags --libs`
DEPS = window.h renderer.h map.h cell.h
OBJ = window.c main.c renderer.c map.c cell.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

AlphaDice: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)