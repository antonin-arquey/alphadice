CC=gcc
CFLAGS= `sdl2-config --cflags --libs`
DEPS = window.h renderer.h map.h arbitre.h interface.h arbre.h
OBJ = window.c main.c renderer.c map.c arbitre.c interface.c arbre.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lm

AlphaDice: $(OBJ)
	gcc -std=c99 -o $@ $^ $(CFLAGS)
