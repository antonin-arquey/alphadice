CC=gcc
CFLAGS= `sdl2-config --cflags --libs`
DEPS = window.h renderer.h map.h arbitre.h libLoader.h player.h log.h
OBJ = window.c main.c renderer.c map.c arbitre.c libLoader.c player.c log.c

%.o: %.c $(DEPS)
	$(CC) -std=c99 -c -o $@ $< $(CFLAGS) -lm

AlphaDice: $(OBJ)
	gcc -g -std=c99 -o $@ $^ $(CFLAGS) -ldl -lSDL2_ttf

clean:
	rm -rf AlphaDice
