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
	nbPlayer = atoi(argv[2]);//car retourne le code ascii sans  - '0'
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
	SMap mapBis =
	/* Boucle du jeu (doit se terminer lorsque l'on ferme la fenêtre ou que l'on quitte proprement le jeu) */
	int cpt=0;
	while(windowIsNotClosed() || cpt<4){
		for(int i = 0; i < nbPlayer; i++){
			printf("Turn to AI %d\n", i);
			sleep(1);
			PlayTurn(i, map, turn);
			printf("Attaque de %d vers %d\n", turn->cellFrom, turn->cellTo);
			if(verifyTurn(i, map, turn) == 1){
				printf("Tour validé ! \n");
				moveTurn(map, turn);
			}
			else{
				printf("Tour non validé ! \n");
			}
			displayMap(renderer,map,matrice_map,turn);
			SDL_RenderPresent(renderer);
			endTurn(i, map);
			SDL_Delay(1000);
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
