CC=gcc
CFLAGS= `sdl2-config --cflags --libs`
DEPS = window.h renderer.h map.h arbitre.h arbre.h gameIA.h
OBJ = window.c main.c renderer.c map.c arbitre.c arbre.c gameIA.c interface.so

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lm

AlphaDice: $(OBJ)
	gcc -g -std=c99 -o $@ $^ $(CFLAGS) -ldl

clean:
	rm -rf AlphaDice interface.o interface.so

interface.so: interface.o
	gcc -shared -o interface.so interface.o && rm -rf interface.o

interface.o: interface.h interface.c
	gcc -fPIC -c interface.c
