#include "cell.h"
#include "renderer.h"
#include <stdlib.h>

typedef struct Map Map;

Map* createMap(int nbPlayer, SDL_Renderer* renderer);
void displayMap(SDL_Renderer* renderer);