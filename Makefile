CC=gcc
CFLAGS= `sdl2-config --cflags --libs -std=c99`
DEPS = window.h renderer.h map.h arbitre.h interface.h arbre.h
OBJ = window.c main.c renderer.c map.c arbitre.c interface.c arbre.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

AlphaDice: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
