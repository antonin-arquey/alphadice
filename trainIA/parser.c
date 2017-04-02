#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char const *argv[]){
	char ch;
	char file_name[25] = "game.log";
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
   	int nb_pays = atoi(str);
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

	while( ( ch = fgetc(fp) ) != '\n'){
		//Fin Map//
	}

	
   	fclose(fp);
   	return 0;
}