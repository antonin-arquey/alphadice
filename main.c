#include <stdlib.h>
#include <stdio.h>
#include "window.h"
#include "renderer.h"
#include "arbitre.h"
#include "map.h"
#include "gameIA.h"
#include "libLoader.h"
#include <unistd.h>

int main(int argc, char* argv[]){
	/* Récupération des paramètres */
	int nbPlayer, nbGame;
	int nbLib = 0;
	if(verifArguments(argc, argv, &nbLib)){
		return 1;
	}
	nbPlayer = atoi(argv[2]);
	nbGame = atoi(argv[1]);

	/* Chargement de la librairie dynamique */
	if(nbLib > 0)
	{
		void **libs;
		playT PlayTurn[nbLib];
		initG InitGame[nbLib];

		if(nbLib == 1) //Si une seule librairie
		{
			libs = loadLib(nbLib, argv[3], NULL, InitGame, PlayTurn);
		}
		else //Si deux libraries
		{
			libs = loadLib(nbLib, argv[3], argv[4], InitGame, PlayTurn);
		}
	}

	int matrice_map[800][600];
	int tab_pays[80][2];


	/*Initialisation du jeu */
	SPlayerInfo *info = malloc(sizeof(SPlayerInfo));
	InitGame[0](1, nbPlayer, info); //id de quel joueur ? *info de quel joueur ?

	/* Création de l'affichage*/
	SDL_Window* window = createWindow();
	SDL_Renderer* renderer = createRenderer(window);

	SDL_Texture *diceTextures[10];
	loadDiceTextures(renderer, diceTextures);

	SMap *map = createMap(nbPlayer, renderer,matrice_map, tab_pays);
	SDL_RenderPresent(renderer);
	displayMap(renderer,map,matrice_map,NULL, tab_pays, diceTextures);
	SDL_RenderPresent(renderer);

	STurn *turn = malloc(sizeof(STurn));
	/* Boucle du jeu (doit se terminer lorsque l'on ferme la fenêtre ou que l'on quitte proprement le jeu) */
	int cpt=0;
	while(cpt<50 && windowIsNotClosed()){
		printf("Tour numero : %d\n", cpt);
		for(int i = 0; i < nbPlayer; i++){
			printf("Copie de la carte\n");
			SMap *mapCopy = deepCopy(map);
			printf("Turn to AI %d\n", i);
			while(PlayTurn[0](i, mapCopy, turn) == 1){//PlayTurn
					//printf("Attaque de %d vers %d\n", turn->cellFrom, turn->cellTo);
					if(verifyTurn(i, map, turn) == 1){
						//printf("Tour validé ! \n");
						moveTurn(map, turn);
						//SDL_Delay(500);
					}
					else{
						printf("Tour non validé ! \n");
					}
				freeMap(mapCopy);
				mapCopy = deepCopy(map);
				displayMap(renderer,map,matrice_map,turn, tab_pays, diceTextures);
				SDL_RenderPresent(renderer);
			}
			if(victoire(i, map)){
				printf("Victoire du joueur %d !!\n", i);
				return 0;
			}
			freeMap(mapCopy);
			endTurn(i, map);
			displayMap(renderer,map,matrice_map,turn, tab_pays, diceTextures);
			SDL_RenderPresent(renderer);
		}
		cpt++;
	}

	freeDiceTextures(diceTextures);
	free(turn);
	freeMap(map);
	free(info);

	/* Ferme le jeu */
	destroyWindow(window, renderer);
	freeLib(libs, nbLib);
	return 0;
}
