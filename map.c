#include "map.h"

struct Map{
    Cell** cells;   // Tableau des cellules
	int n_cells;   // Nombre de cellules
};

Map* createMap(int nbPlayer){
	Map* map = (Map*) malloc(sizeof(struct Map));
	//displayMap();
	return map;
}