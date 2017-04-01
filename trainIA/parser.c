#include <stdio.h>
#include <stdlib.h>

#include "log.h"

int valeur(char str[], int a, int b){
	int compteur = 0;
	char strVal[5];
	for (int i = 0; i < 100; ++i){
		//printf("%d ", str[i]);
		if (compteur == a){
			sprintf(strVal, "%d", str[i]);
		}
		if (str[i] == '/'){
			printf("oui\n");
			compteur += 1;
			if(compteur == b)
				return atoi(strVal);
		}
	}
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
 	char str[10];
   	while( ( ch = fgetc(fp) ) != '\n'){
		sprintf(str, "%d", ch);
   	}
   	int nb_pays = atoi(str);
   	int mat_map[800][600];
   	int tabPays[nb_pays][2];
   	int tab_owner[nb_pays];
 	int tab_de[nb_pays];
   	printf("%d\n", nb_pays);
 	
 	for (int i = 0; i < nb_pays; ++i){
 		char str[100];
 		while( ( ch = fgetc(fp) ) != '\n'){
			sprintf(str, "%d", ch);
	   	}


	   	tab_owner[i] = valeur(str,1,2);
	   	tab_de[i] = valeur(str,4,5);
	   	tabPays[i][0] = valeur(str,2,3);
		tabPays[i][1] = valeur(str,3,4);
		printf("%d %d %d %d\n", tab_owner[i], tab_de[i], tabPays[i][0], tabPays[i][1]);
 	}


	while( ( ch = fgetc(fp) ) != '\n'){
		//sprintf(str, "%d", ch);
	}
	
   	fclose(fp);
   	return 0;
}