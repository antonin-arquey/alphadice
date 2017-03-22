CC=gcc
CFLAGS= `sdl2-config --cflags --libs`
DEPS = window.h renderer.h map.h arbitre.h libLoader.h player.h
OBJ = window.c main.c renderer.c map.c arbitre.c libLoader.c player.c

%.o: %.c $(DEPS)
	$(CC) -std=c99 -c -o $@ $< $(CFLAGS) -lm

AlphaDice: $(OBJ)
	gcc -g -std=c99 -o $@ $^ $(CFLAGS) -ldl

clean:
	rm -rf AlphaDice
