#include "map.h"
#include "interface.h"
#include <time.h>
#include <unistd.h>

//matrice de la map
int size_map_h=800;
int size_map_l=600;
//int mat_map[size_map_h][size_map_l];

int aleatoire(int a, int b){
	return rand() % (b-a+1) + a;
}

// Fonction initialisant la carte et l'affichant sur le renderer
SMap* createMap(int nbPlayer, SDL_Renderer* renderer, int mat_map[size_map_h][size_map_l], int tabPays[][2]){
	srand(time(NULL));
	//creation des elements de la map : map et ces territoires
	int nb_pays = aleatoire(30,60);
	int nb_de = (int) (nb_pays * 2)/nbPlayer;
	SMap *map = malloc(sizeof(SMap));
	SCell *territoires = malloc(sizeof(SCell) * nb_pays);

	//initilialisation des propriétés de la map
	int reserve[nbPlayer];
	int deJoueur[nbPlayer];
	for(int i = 0; i < nbPlayer; i++){
		reserve[i] = 0;
		deJoueur[i] = nb_de;
	}
	map->cells = territoires;
	map->nbCells = nb_pays;
	map->stack = reserve;

	//initilialisation des id des cellules de la map
	for(int i = 0; i < nb_pays; i++){
		territoires[i].id = i;
		territoires[i].nbNeighbors = 0;
		territoires[i].neighbors = malloc(sizeof(SCell*)*nb_pays);
	}
	//tirages aux sorts des joueurs possédant les territoires
	for(int i = 0; i < nb_pays; i++){
		territoires[i].owner = aleatoire(0,nbPlayer-1);//numero du player
	}
	//repartition des dés des joueurs
	int de;
	for(int i = 0; i < nb_pays; i++){
		if (deJoueur[territoires[i].owner] < 4){
			de = aleatoire(0, deJoueur[territoires[i].owner]);
		}else{
			de = aleatoire(0,4);
		}
		deJoueur[territoires[i].owner] -= de;
		territoires[i].nbDices = 1 + de;
	}

	//affichage pour voir s'il reste des dés
	for(int i = 0; i < nbPlayer; i++){
		printf("Il reste %d dés pour le joueur %d\n", deJoueur[i], i);
	}


	/*Initialisation graphique de la map*/
	int border = 25; //bordure pour que les centres des territoires ne soient pas trop sur les bords.
	for (int j=0;j<size_map_h;j++){
		for (int k=0;k<size_map_l;k++){
			mat_map[j][k]=-1;
		}
	}

	//génération des centres des territoires;
	for (int j=0;j<nb_pays;j++){
		int i; int k;
		i = aleatoire(border,size_map_h - border);
		k = aleatoire(border,size_map_l - border);
		mat_map[i][k]=j;
		tabPays[j][0]=i;
		tabPays[j][1]=k;
	}
	printf("Germe territoire crées\n");
	//génération des territoires
	for (int j=0;j<size_map_h;j++){
		for (int k=0;k<size_map_l;k++){
			double distance = 10000000;
			int paysPlusProche;
			double new_distance;
			for (int f=0;f<nb_pays;f++){
				new_distance = getDistance(tabPays[f][0],tabPays[f][1],j,k);
				//calcul de la distance
				if (new_distance<distance){
					distance = new_distance;
					paysPlusProche = f;
				}
			}
			mat_map[j][k] = paysPlusProche;
		}
	}

	//Génération des voisins
	for (int j=1;j<size_map_h;j++){
		for (int k=1;k<size_map_l;k++){
			if (mat_map[j][k] != mat_map[j-1][k]){
				if (isVoisin(map,mat_map[j][k],mat_map[j-1][k]) == 0){
					addVoisin(map,mat_map[j][k],mat_map[j-1][k]);
				}
			}
			if(mat_map[j][k] != mat_map[j][k-1]){
				if (isVoisin(map,mat_map[j][k],mat_map[j][k-1]) == 0){
					addVoisin(map,mat_map[j][k],mat_map[j][k-1]);
				}
			}
			/*if(mat_map[j][k] != mat_map[j-1][k-1]){
				//printf("diff");
				if (isVoisin(map,mat_map[j][k],mat_map[j][k-1]) == 0){
					addVoisin(map,mat_map[j][k],mat_map[j-1][k-1]);
				}
			}*/
		}
	}

	for (int j=0;j<size_map_h/20;j++){
		for (int k=0;k<size_map_l/20;k++){
			printf("%d ",mat_map[j][k]);
		}
		printf("\n");
	}

	for(int i = 0; i < nb_pays; i++){
		printf("Territoire id = %d\n",territoires[i].id);
		printf("nbVoisins = %d\n",territoires[i].nbNeighbors);
		printf("Voisins :\n");
		for(int j=0;j<territoires[i].nbNeighbors;j++)
		{
			printf("%d ",territoires[i].neighbors[j]->id);
		}
		printf("\n");
	}

	return map;
}

int isVoisin(SMap *map, int t1, int t2){
	//fonction qui regarde si les cellules c1 et c2 sont déjà voisines
	//renvoie 1 si oui, 0 sinon.
	SCell *territoires = map->cells;
	for(int i=0;i<(territoires[t1].nbNeighbors);i++){
		if(territoires[t1].neighbors[i]->id == t2)
		{
			return 1;
		}
	}
	return 0;
}

void addVoisin(SMap *map, int t1, int t2){
	map->cells[t1].neighbors[map->cells[t1].nbNeighbors] = &(map->cells[t2]);
	map->cells[t1].nbNeighbors++;
	map->cells[t2].neighbors[map->cells[t2].nbNeighbors] = &(map->cells[t1]);
	map->cells[t2].nbNeighbors++;
}

// Fonction affichant la carte sur le renderer
void displayMap(SDL_Renderer* renderer, SMap *map,int mat_map[size_map_h][size_map_l],STurn *turn, int tabPays[][2], SDL_Texture *diceTextures[]){
	int tabColor[8][4]={{242,202,39,1},
	{44,195,107,1},{236,94,0,1},
	{231,76,60,1},{102,0,153,1},
	{44,62,80,1},{52,152,219,1},
	{163,177,178,1}};
	//Jaune Vert Orange Rose Violet Bleufoncé Bleuclair
	for (int j=0;j<size_map_h;j++){
		for (int k=0;k<size_map_l;k++){
			//Affichage des bordures
			if (turn != NULL && turn->cellFrom == mat_map[j][k]){
				SDL_SetRenderDrawColor(renderer,255,255,255,255);
			}else if (turn != NULL && turn->cellTo == mat_map[j][k]){
				SDL_SetRenderDrawColor(renderer,0,0,0,0);
			}else if(mat_map[j][k] != mat_map[j-1][k] || mat_map[j][k] != mat_map[j][k-1] || mat_map[j][k] != mat_map[j-1][k-1]){
				SDL_SetRenderDrawColor(renderer,0,0,0,0);
			}else{
			//Affichage des couleurs des territoires
				SDL_SetRenderDrawColor(renderer,tabColor[map->cells[mat_map[j][k]].owner][0],tabColor[map->cells[mat_map[j][k]].owner][1],tabColor[map->cells[mat_map[j][k]].owner][2],tabColor[map->cells[mat_map[j][k]].owner][3]);
			}
			createPoint(renderer,j,k);
		}
	}

	for(int i = 0 ; i < map->nbCells ; i++)
	{
			SDL_Texture *diceTexture;
			if(map->cells[i].nbDices < 9)
			{
				diceTexture = diceTextures[map->cells[i].nbDices];
			}
			else{
				diceTexture = diceTextures[9];
			}

			SDL_Rect position;


			//Recuperation de la taille de l'image dans position.w et position.h
			SDL_QueryTexture(diceTexture, NULL, NULL, &position.w, &position.h);

			//Position de l'image X Y
			position.x = tabPays[i][0];
			position.y = tabPays[i][1];
			position.w /= 2;
			position.h /= 2;
			//Texture appliqué au renderer
			SDL_RenderCopy(renderer, diceTexture, NULL, &position);
	}
}

double getDistance(int x1, int y1, int x2, int y2){
	double d1 = (x2-x1);
	double d2 = (y2-y1);
	if (d1 < 0){
		d1 = -1*d1;
	}
	if(d2< 0){
		d2 = -1 * d2;
	}
	/*double d1 = (x2-x1)*(x2-x1);
	double d2 = (y2-y1)*(y2-y1);*/
	return (d1+d2);
}

void loadDiceTextures(SDL_Renderer* renderer, SDL_Texture *diceTextures[])
{
	char filename[20] = "valeur/0.bmp";
	for(int i = 0 ; i < 9 ; i++)
	{
		char test = i + '0' ;
		printf("char : %c\n", test);
		printf("%s\n", filename);
		printf("%c\n", filename[7]);
		filename[7] = test;
		printf("%s\n", filename);
		SDL_Surface* image = SDL_LoadBMP(filename);
		if(!image)
		{
				printf("Erreur de chargement de l'image : %s",SDL_GetError());
				exit(-1);
		}

		diceTextures[i] = SDL_CreateTextureFromSurface(renderer,image);
		SDL_FreeSurface(image);
	}
}

void freeDiceTextures(SDL_Texture *diceTextures[])
{
	for(int i=0 ; i < 10; i++)
	{
		SDL_DestroyTexture(diceTextures[i]);
	}
}
