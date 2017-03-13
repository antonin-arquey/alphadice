#include "map.h"
#include "interface.h"


int aleatoire(int a, int b){
	return 1;
}

// Fonction initialisant la carte et l'affichant sur le renderer
SMap* createMap(int nbPlayer, SDL_Renderer* renderer){
	SMap *map = malloc(sizeof(SMap));

	int reserve[8] = {0,0,0,0,0,0,0,0};
	map->nbCells = aleatoire(30, 60);
	map->stack = reserve;
	return map;
}

// Fonction affichant la carte sur le renderer
// Actuellement en test afin d'afficher juste 
// des hexagones sur la taille de la map
void displayMap(SDL_Renderer* renderer, SMap *map){
	int i=0, j=0, ligne=1;
	for(;j<600;j+=15){
		for(;i<790;i+=20){
			createHexagone(renderer, i, j);
		}
		i=0;
		if (ligne%2==1){
			i+=10;
		}
		ligne+=1;		
	}
}

