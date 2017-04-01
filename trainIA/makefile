CC=gcc
CFLAGS= `sdl2-config --cflags --libs`
DEPS = log.h
OBJ = parser.c log.c

%.o: %.c $(DEPS)
	$(CC) -std=c99 -c -o $@ $< $(CFLAGS) -lm

parser: $(OBJ)
	gcc -g -std=c99 -o $@ $^ $(CFLAGS) -ldl

clean:
	rm -rf parser
