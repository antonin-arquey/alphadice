CC=gcc
CFLAGS= `sdl2-config --cflags --libs` -lSDL2_image
DEPS =
OBJ = test.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lm

test: $(OBJ)
	gcc -g -std=c99 -o $@ $^ $(CFLAGS)

clean:
	rm -rf test
