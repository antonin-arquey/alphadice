#include "map.h"
#include "interface.h"
#include <time.h>
#include <unistd.h>

//matrice de la map
int size_map_h=800;
int size_map_l=600;


// Fonction initialisant la carte et l'affichant sur le renderer
SMap* createMap(int nbPlayer, int nb_pays, int tab_owner[], int tab_de[], int mat_map[size_map_h][size_map_l], int tabPays[][2]){

	SMap *map = malloc(sizeof(SMap));

	//Creation des stacks
	map->stack = malloc(nbPlayer * sizeof(unsigned int));

	SCell *territoires = malloc(sizeof(SCell) * nb_pays);

	//initilialisation des propriétés de la map
	for(int i = 0; i < nbPlayer; i++)
		map->stack[i] = 0;

	map->cells = territoires;
	map->nbCells = nb_pays;

	//initilialisation des id des cellules de la map
	for(int i = 0; i < nb_pays; i++){
		territoires[i].id = i;
		territoires[i].nbNeighbors = 0;
		territoires[i].neighbors = malloc(sizeof(SCell*)*nb_pays);
	}
	//repartition territoires et des dés
	for(int i = 0; i < nb_pays; i++){
		territoires[i].owner = tab_owner[i];//numero du player
		territoires[i].nbDices = tab_de[i];
	}

	/*Initialisation graphique de la map*/
	int border = 25; //bordure pour que les centres des territoires ne soient pas trop sur les bords.
	for (int j=0;j<size_map_h;j++){
		for (int k=0;k<size_map_l;k++){
			mat_map[j][k]=-1;
		}
	}

	//génération des territoires
	for (int j=0;j<size_map_h;j++){
		for (int k=0;k<size_map_l;k++){
			double distance = 10000000;
			int paysPlusProche;	double new_distance;
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

	//modification des centres de la table Pays pour afficher les images au centre
	/*long compteurX, compteurY, compteur;
	for(int k = 0; k < nb_pays; k++){
		compteurX = 0; compteur = 0;
		compteurY = 0;
		for(int j = 0; j < size_map_h; j++){
			for(int i = 0; i < size_map_l; i ++){
				if(mat_map[j][i] == k){
					compteurX += j; compteurY += i; compteur += 1;
				}
			}
		}
		compteurX /= compteur; compteurY /= compteur;
		tabPays[k][0] = compteurX; tabPays[k][1] = compteurY;
	}*/

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
		}
	}
	return map;
}

int isVoisin(SMap *map, int t1, int t2){
	//fonction qui regarde si les cellules c1 et c2 sont déjà voisines
	//renvoie 1 si oui, 0 sinon.
	SCell *territoires = map->cells;
	for(int i=0;i<(territoires[t1].nbNeighbors);i++){
		if(territoires[t1].neighbors[i]->id == t2)
			return 1;
	}
	return 0;
}

void addVoisin(SMap *map, int t1, int t2){
	map->cells[t1].neighbors[map->cells[t1].nbNeighbors] = &(map->cells[t2]);
	map->cells[t1].nbNeighbors++;
	map->cells[t2].neighbors[map->cells[t2].nbNeighbors] = &(map->cells[t1]);
	map->cells[t2].nbNeighbors++;
}


double getDistance(int x1, int y1, int x2, int y2){
	double d1 = (x2-x1);
	double d2 = (y2-y1);
	if (d1 < 0)
		d1 = -d1;

	if(d2 < 0)
		d2 = -d2;

	return (d1+d2);
}
