#include "map.h"
#include "interface.h"
#include <time.h>


int aleatoire(int a, int b){
	return rand() % (b-a+1) + a;
}

// Fonction initialisant la carte et l'affichant sur le renderer
SMap* createMap(int nbPlayer, SDL_Renderer* renderer){
	SMap *map = malloc(sizeof(SMap));

	int reserve[8] = {0,0,0,0,0,0,0,0};
	map->nbCells = aleatoire(30, 60);
	map->stack = reserve;
	return map;
}

// Fonction affichant la carte sur le renderer
// Actuellement en test afin d'afficher juste 
// des hexagones sur la taille de la map
void displayMap(SDL_Renderer* renderer, SMap *map2){
	/*int i=0, j=0, ligne=1;
	for(;j<600;j+=15){
		for(;i<790;i+=20){
			createHexagone(renderer, i, j);
		}
		i=0;
		if (ligne%2==1){
			i+=10;
		}
		ligne+=1;		
	}*/

	srand(time(NULL));
	int size_map_h=800;
	int size_map_l=600;
	int border = 50; //bordure pour pas que les territoires sur les bords soient trop petit
	int nb_pays=aleatoire(30,60);
	int map[size_map_h][size_map_l];
	int tabPays[nb_pays][2];
	double distance;
	for (int j=0;j<size_map_h;j++){
		for (int k=0;k<size_map_l;k++){
			map[j][k]=0;
		}
	}
	
	//génération des centres des pays;
	for (int j=1;j<nb_pays+1;j++){
		int i; int k;
		i = aleatoire(border,size_map_h - border);
		k = aleatoire(border,size_map_l - border);
		map[i][k]=j;
		tabPays[j][0]=i;
		tabPays[j][1]=k;
		//printf("Pays %d : %d %d\n",j,i,k);
	}

	for (int j=0;j<size_map_h;j++){
		for (int k=0;k<size_map_l;k++){
			distance = 10000000;
			int paysPlusProche = 1;
			double new_distance;
			int f;
			for (f=0;f<nb_pays;f++){
				new_distance = getDistance(tabPays[f][0],tabPays[f][1],j,k);
				//new_distance=sqrt(pow((tabPays[f][0]-j),2)+pow((tabPays[f][1]-k),2));
				//calcul de la distance
				if (new_distance<distance){
					distance = new_distance;
					paysPlusProche = f;
				}
			}
			map[j][k] = paysPlusProche;
			SDL_SetRenderDrawColor(renderer,paysPlusProche*25,paysPlusProche*25,paysPlusProche*25,paysPlusProche*25);
			createPoint(renderer,j,k);
		}
	}
	
	/*//affichage de la map
	for (int j=0;j<size_map_h;j++){
		for (int k=0;k<size_map_l;k++){
			printf("%d ",map[j][k]);
		}
		//printf("\n");
	}*/
}

double getDistance(int x1, int y1, int x2, int y2){
	/*double d1 = pow((x2-x1),2);
	double d2 = pow((y2-y1),2);*/
	double d1 = (x2-x1)*(x2-x1);
	double d2 = (y2-y1)*(y2-y1);
	return (d1+d2);
}

