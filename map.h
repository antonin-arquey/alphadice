#include "interface.h"
#include "renderer.h"

// Fonction initialisant la carte et l'affichant sur le renderer
SMap* createMap(int nbPlayer, SDL_Renderer* renderer);

// Fonction affichant la carte sur le renderer
// Actuellement en test afin d'afficher juste 
// des hexagones sur la taille de la map
void displayMap(SDL_Renderer* renderer);
