#include <stdlib.h>
#include <stdio.h>
#include "window.h"
#include "renderer.h"
#include "arbitre.h"
#include "map.h"
#include "interface.h"
#include <unistd.h>


int main(int argc, char* argv[]){
	/* Récupération des paramètres */
	int nbPlayer, nbGame;
	if(verifArguments(argc, argv)){
		return 1;
	}
	nbPlayer = atoi(argv[2]);
	nbGame = atoi(argv[1]);
	int matrice_map[800][600];
	/*Initialisation du jeu */
	SPlayerInfo *info = malloc(sizeof(SPlayerInfo));
	InitGame(1, nbPlayer, info); //id de quel joueur ? *info de quel joueur ?

	/* Création de l'affichage*/
	SDL_Window* window = createWindow();
	SDL_Renderer* renderer = createRenderer(window);
	SMap *map = createMap(nbPlayer, renderer,matrice_map);
	SDL_RenderPresent(renderer);
	displayMap(renderer,map,matrice_map,NULL);
	SDL_RenderPresent(renderer);

	STurn *turn = malloc(sizeof(STurn));
	/* Boucle du jeu (doit se terminer lorsque l'on ferme la fenêtre ou que l'on quitte proprement le jeu) */
	int cpt=0;
	while(cpt<25){
		printf("Tour numero : %d\n", cpt);
		for(int i = 0; i < nbPlayer; i++){
			printf("Turn to AI %d\n", i);
			while(PlayTurn(i, map, turn) == 1){
					printf("Attaque de %d vers %d\n", turn->cellFrom, turn->cellTo);
					if(verifyTurn(i, map, turn) == 1){
						printf("Tour validé ! \n");
						moveTurn(map, turn);
						if(victoire(i, map)){
							printf("Victoire du joueur %d !!\n", i);
							return 0;
						}
					}
					else{
						printf("Tour non validé ! \n");
					}
				displayMap(renderer,map,matrice_map,turn);
				SDL_RenderPresent(renderer);
			}
			endTurn(i, map);
			displayMap(renderer,map,matrice_map,turn);
			SDL_RenderPresent(renderer);
		}
		cpt++;
	}

	free(turn);
	free(map);
	free(info);
	
	/* Ferme le jeu */
	destroyWindow(window, renderer);
	return 0;
}
