
libIA2.so: interface.o gameIA.o
	gcc -shared -o libIA2.so interface.o gameIA.o && rm -rf interface.o gameIA.o

interface.o: interface.h interface.c gameIA.h
	gcc -fPIC -c interface.c -std=c99

gameIA.o: interface.h arbre.h gameIA.h gameIA.c
	gcc -fPIC -c gameIA.c -std=c99
