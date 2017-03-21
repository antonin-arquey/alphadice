
libIA.so: interface.o gameIA.o arbre.o
	gcc -shared -o libIA.so interface.o gameIA.o arbre.o && rm -rf interface.o arbre.o gameIA.o

interface.o: interface.h interface.c gameIA.h
	gcc -fPIC -c interface.c -std=c99

gameIA.o: interface.h arbre.h gameIA.h gameIA.c
	gcc -fPIC -c gameIA.c -std=c99
	
arbre.o: arbre.h
	gcc -fPIC -c arbre.c -std=c99