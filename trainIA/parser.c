#include <stdio.h>
#include <stdlib.h>
#include "map.h"


/*Ce code aurait servit à parser l'ensemble des fichiers de log pour pouvoir après extraire des paramêtres de mouvement
  et ensuite apprendre par apprentissagesupervisé une fonction d'évaluation des maps plus optimisé que celle que l'on a 
  au niveau des feuilles de l'arbre de recherche */

//fonction qui retourne la valeur entre la a eme virgule et la b eme
int valeur(char *str, int a, int b){
	int compteur = 0;
	char strVal[100];
	int c = 0;
	for (int i = 0; i < 100; ++i){
		if (compteur == a)
			strVal[c++] = str[i];

		if (str[i] == ','){
			compteur += 1;
			if(compteur == b)
				return atoi(strVal);
		}
	}
}

//fonction qui simule une attaque raté
void moveTurnFail(SMap *map, STurn *turn){
	map->cells[turn->cellFrom].nbDices = 1;
}

//fonction qui simule le succès d'une attaque
void moveTurnWin(SMap *map, STurn *turn){
	SCell *cellAttacker = &map->cells[turn->cellFrom];
	SCell *cellDefender = &map->cells[turn->cellTo];
	cellDefender->owner = cellAttacker->owner;
	cellDefender->nbDices = cellAttacker->nbDices - 1;
	cellAttacker->nbDices = 1;
}

int main(int argc, char const *argv[]){
	char ch;
	char file_name[25] = "game2.log";
  	FILE *fp;
 
   	fp = fopen(file_name,"r"); // read mode
 
   	if( fp == NULL )
   	{
    	perror("Error while opening the file.\n");
     	exit(EXIT_FAILURE);
   	}
   	

 	char *str = malloc(sizeof(char)*100);
 	int c = 0;
   	while( ( ch = fgetc(fp) ) != '\n'){
		str[c++] = ch;
	}
   	int nb_pays = valeur(str,0,1);
   	int nbPlayer = valeur(str,1,2);
   	int mat_map[800][600];
   	int tabPays[nb_pays][2];
   	int tab_owner[nb_pays];
 	int tab_de[nb_pays];
   	printf("%d\n", nb_pays);
 	free(str);

 	for (int i = 0; i < nb_pays; ++i){
 		char *str = malloc(sizeof(char) * 100);
 		c = 0;
 		while( ( ch = fgetc(fp) ) != '\n'){
			str[c++] = ch;
	   	}
	   	tab_owner[i] = valeur(str,1,2);
	   	tab_de[i] = valeur(str,4,5);
	   	tabPays[i][0] = valeur(str,2,3);
		tabPays[i][1] = valeur(str,3,4);
		printf("%d %d %d %d\n", tab_owner[i], tab_de[i], tabPays[i][0], tabPays[i][1]);
		free(str);
 	}

 	SMap *map = createMap(nbPlayer, nb_pays, tab_owner, tab_de, mat_map, tabPays);

	while( ( ch = fgetc(fp) ) != '\n'){
		//Fin Map//
	}

	STurn *turn = malloc(sizeof(STurn));

	int a = 0;
	while(1){
		printf("tour : %d\n", a++);
		while( ((ch = fgetc(fp) ) != '/') && ((ch = fgetc(fp) ) != '#')){
			char *str = malloc(sizeof(char) * 100);
	 		c = 0;
			while( ( ch = fgetc(fp) ) != '\n'){
				str[c++] = ch;
		   	}
		   	turn->cellFrom = valeur(str,1,2);
		   	turn->cellTo =  valeur(str,2,3);
		   	if(valeur(str,3,4) > valeur(str,4,5))
		   		moveTurnWin(map, turn);
		   	else
		   		moveTurnFail(map, turn);
		   	free(str);
		}

		if(ch == '#')//Fin du fichier
			break;

		while( ( ch = fgetc(fp) ) != '\n'){
			//repartition dés//
		}

		while( (ch = fgetc(fp) ) != '/'){
			char *str = malloc(sizeof(char) * 100);
	 		c = 0;
			while( ( ch = fgetc(fp) ) != '\n'){
				str[c++] = ch;
		   	}
		   	map->cells[valeur(str,0,1)].nbDices += 1;
		   	free(str);
		}
		if((ch = fgetc(fp) ) == 'F'){
			while( ( ch = fgetc(fp) ) != '\n'){
				//Fin répartition//
			}
		} else{//recupération du nombre de dices stackés
			char *str = malloc(sizeof(char) * 100);
	 		c = 0;
			while( ( ch = fgetc(fp) ) != '\n'){
				str[c++] = ch;
		   	}
		   	map->stack[valeur(str,0,1)] = valeur(str,1,2);
		   	free(str);
		}
	}

   	fclose(fp);
   	return 0;
}