#include <stdlib.h>
#include <stdio.h>

int main (int argc,char* argv[]){
	FILE *fp;
	char buff[255];
	int i, nbTer, etat = 0;
	
	fp = fopen("game.log", "r");
	fscanf(fp, "%s", buff);
	printf("nbTer : %s\n", buff );
	nbTer = atoi(buff);
	lseek(fp, +2, SEEK_CUR);
	for(i=0; i <= nbTer; i++){
		fgets(buff, 255, (FILE*)fp);
		if(i>0){
			printf("Coordonnées Terrain %d : %s\n", i, buff );
		}
	}
	
	do{
		lseek(fp, -1, SEEK_CUR);
		switch(etat){
			//case 0 : case nothing
			case 0 : 
				lseek(fp, +1, SEEK_CUR);
				etat=1;
				break;
			//case 1 : case tour
			case 1 : 
				//fscanf(fp, "%s", buff); //Prends un caractere
				fgets(buff, 255, (FILE*)fp); //Prends une ligne
				printf("1 : %s\n", buff );
				break;
		}
	}while(fgetc(fp) != EOF);
	
}