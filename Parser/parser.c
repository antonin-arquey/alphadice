#include <stdlib.h>
#include <stdio.h>

int main (int argc,char* argv[]){
	FILE *fp;
	char buff[255];
	int i, nbTer, etat = 0;
	char caract;
	
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
		fseek(fp, -1, SEEK_CUR);
		fgets(buff, 255, (FILE*)fp); //Prends une ligne
		strtok(buff, "\n");
		//printf("%s\n",buff );
		if((strncmp(buff,"/-/",3))==0){
			etat=4;
		}else if((strncmp(buff,"///",3))==0){
			etat=4;
		}else if((strncmp(buff,"###",3))==0){
			etat=4;
		}
		
		switch(etat){
			//case 0 : case nothing
			case 0 : 
				//lseek(fp, +1, SEEK_CUR);
				etat=1;
				break;
			//case 1 : case tour
			case 1 : 
				printf("YOLO à nous le jeux\n");
				break;
			// Fin d'un tour
			case 2 :
				printf("FIN d'un tour\n");
				printf("Le terrain n°%s reçoit un dé\n", buff);
				break;
			case 3 :
				printf("The Winner is\n");
				break;
			case 4 :
				if((strncmp(buff,"/-/",3))==0){
					etat=1;
				}else if((strncmp(buff,"///",3))==0){
					etat=2;
				}else if((strncmp(buff,"###",3))==0){
					etat=3;
				}
		}
		caract = fgetc(fp);
	}while(caract != EOF);
	
}