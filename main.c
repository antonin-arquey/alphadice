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
#include <SDL2/SDL_ttf.h>

int main(int argc, char* argv[]){
	/* Récupération des paramètres */
	int nbPlayer, nbGame;
	int nbLib = 0;
	int matrice_map[WIN_WIDTH][WIN_HEIGHT];
	int tab_pays[80][2];

	if(verifArguments(argc, argv, &nbLib)){
		return 1;
	}
	nbPlayer = atoi(argv[2]);
	nbGame = atoi(argv[1]);
	printf("Paramètres de la partie :\n\t Nombre de parties : %d\n\t Nombre de joueurs %d (%d IA / %d interactifs)\n", nbGame, nbPlayer, nbLib, nbPlayer-nbLib);

	// Chargement de la librairie dynamique
	void **libs;
	playT PlayTurn[nbLib];
	initG InitGame[nbLib];
	endG EndGame[nbLib];


	if(nbLib > 0) //Si au moins une lib dynamique a charger
	{
		libs = loadLib(nbLib, argv, InitGame, PlayTurn, EndGame);
	}

	/*Initialisation des IA */
	SPlayerInfo **info = malloc(nbLib * sizeof(SPlayerInfo *));
	for(int i=0 ; i < nbLib ; i++){
		info[i] = malloc(sizeof(SPlayerInfo));
		InitGame[i](nbPlayer - i - 1, nbPlayer, info[i]);
	}


	/* Création de l'affichage*/
	SDL_Window* window = createWindow();
	SDL_Renderer* renderer = createRenderer(window);

	SDL_Texture *diceTextures[65];
	loadDiceTextures(renderer, diceTextures);
	TTF_Init();
	SMap *map = NULL;

	STurn *turn = malloc(sizeof(STurn));
	// Boucle du jeu (doit se terminer lorsque l'on ferme la fenêtre ou que l'on quitte proprement le jeu)
	for(int p=0 ; p < nbGame ; p++)
	{
		int vic = 0;
		printf("GAME %d / %d\n", p+1, nbGame);
		map = createMap(nbPlayer, renderer, matrice_map, tab_pays);
		SDL_RenderPresent(renderer);
		displayMap(renderer,map,matrice_map,NULL, tab_pays, diceTextures, 0);
		SDL_RenderPresent(renderer);

		while(windowIsNotClosed() && !vic){
			for(int i = 0; i < nbPlayer; i++){
				//Tour des joueurs humains
				if(i+nbLib < nbPlayer){
					printf("Turn to Player %d\n", i);
					displayMap(renderer,map,matrice_map,turn, tab_pays, diceTextures, i);
					SDL_RenderPresent(renderer);
					while(PlayerTurn(i, map, matrice_map, turn, diceTextures, renderer, tab_pays)){
			      verify(i, map, turn);
						displayMap(renderer,map,matrice_map,turn, tab_pays, diceTextures, i);
						SDL_RenderPresent(renderer);
			    }
				}
				else{ //Tour des IA
					SMap *mapCopy = deepCopy(map, nbPlayer);
					printf("Turn to AI %d\n", i);
					while(PlayTurn[0](i, mapCopy, turn)){
						if(!verify(i, map, turn))
							break;
						freeMap(mapCopy);
						mapCopy = deepCopy(map, nbPlayer);
						displayMap(renderer,map,matrice_map,turn, tab_pays, diceTextures, i);
						SDL_RenderPresent(renderer);
					}
					freeMap(mapCopy);
				}

				if(victoire(i, map)){
					char str[20];
					sprintf(str, "###\n%d\n###\n",  i);
					Log(str);
					printf("Victoire du joueur %d !!\n", i);
					vic = 1;
				}
				else{
					endTurn(i, map);
				}
				displayMap(renderer,map,matrice_map,turn, tab_pays, diceTextures, i);
				SDL_RenderPresent(renderer);
			}
		}
	}


	freeDiceTextures(diceTextures);
	free(turn);
	freeMap(map);
	for(int k=0 ; k < nbLib ; k++){
		free(info[k]);
	}
	free(info);

	// Ferme le jeu
	TTF_Quit();
	destroyWindow(window, renderer);
	freeLib(libs, nbLib);
	return 0;
}
