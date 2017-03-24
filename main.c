#include <stdlib.h>
#include <stdio.h>
#include "window.h"
#include "renderer.h"
#include "arbitre.h"
#include "map.h"
#include "libLoader.h"
#include "log.h"
#include "player.h"
#include <unistd.h>

int main(int argc, char* argv[]){
	/* Récupération des paramètres */
	int nbPlayer, nbGame;
	int nbLib = 0;
	int matrice_map[800][600];
	int tab_pays[80][2];

	if(verifArguments(argc, argv, &nbLib)){
		return 1;
	}
	printf("combien de lib ? %d\n", nbLib);
	nbPlayer = atoi(argv[2]);
	nbGame = atoi(argv[1]);

	void **libs;
	playT PlayTurn[nbPlayer];
	initG InitGame[nbPlayer];
	// Chargement de la librairie dynamique

	if(nbLib == 1) //Si une seule librairie
	{
		libs = loadLib(nbLib, argv[3], NULL, InitGame, PlayTurn);
	}
	else if(nbLib == 2)//Si deux libraries
	{
		libs = loadLib(nbLib, argv[3], argv[4], InitGame, PlayTurn);
	}


	/*Initialisation du jeu */
	SPlayerInfo *info = malloc(sizeof(SPlayerInfo));
	//InitGame[0](1, nbPlayer, info); //id de quel joueur ? *info de quel joueur ?

	/* Création de l'affichage*/
	SDL_Window* window = createWindow();
	SDL_Renderer* renderer = createRenderer(window);

	SDL_Texture *diceTextures[10];
	loadDiceTextures(renderer, diceTextures);

	SMap *map = createMap(nbPlayer, renderer, matrice_map, tab_pays);
	SDL_RenderPresent(renderer);
	displayMap(renderer,map,matrice_map,NULL, tab_pays, diceTextures);
	SDL_RenderPresent(renderer);


	STurn *turn = malloc(sizeof(STurn));
	// Boucle du jeu (doit se terminer lorsque l'on ferme la fenêtre ou que l'on quitte proprement le jeu)
	int cpt=0;
	while(cpt<100 && windowIsNotClosed()){
		printf("Tour numero : %d\n", cpt);
    while(PlayerTurn(0, map, matrice_map, turn, diceTextures, renderer, tab_pays)){
      verify(0, map, turn);
			displayMap(renderer,map,matrice_map,turn, tab_pays, diceTextures);
			SDL_RenderPresent(renderer);
    }
    endTurn(0, map);
		for(int i = 1; i < nbPlayer; i++){
			SMap *mapCopy = deepCopy(map);
			printf("Turn to AI %d\n", i);
			while(PlayTurn[0](i, mapCopy, turn)){
				verify(i, map, turn);
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

	// Ferme le jeu
	destroyWindow(window, renderer);
	freeLib(libs, nbLib);
	return 0;
}
