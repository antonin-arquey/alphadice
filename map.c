#include "map.h"

// Structure de la carte
struct Map{
    SCell** cells;   // Tableau des cellules
	int n_cells;   // Nombre de cellules
};

// Fonction initialisant la carte et l'affichant sur le renderer
Map* createMap(int nbPlayer, SDL_Renderer* renderer){
	Map* map = (Map*) malloc(sizeof(struct Map));
	displayMap(renderer);
	return map;
}

// Fonction affichant la carte sur le renderer
// Actuellement en test afin d'afficher juste 
// des hexagones sur la taille de la map
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

