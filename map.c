#include "map.h"

struct Map{
    Cell** cells;   // Tableau des cellules
	int n_cells;   // Nombre de cellules
};

Map* createMap(int nbPlayer, SDL_Renderer* renderer){
	Map* map = (Map*) malloc(sizeof(struct Map));
	displayMap(renderer);
	return map;
}

void displayMap(SDL_Renderer* renderer){
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

