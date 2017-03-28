#include <stdlib.h>
#include <stdio.h>

int main (int argc,char* argv[]){
	FILE *fp;
	char buff[255];
	int i, nbTer;
	
	fp = fopen("game.log", "r");
	fscanf(fp, "%s", buff);
	printf("1 : %s\n", buff );
	nbTer = atoi(buff);
	
	for(i=0; i < nbTer; i++){
		
	}
	
	fscanf(fp, "%s", buff);
	printf("1 : %s\n", buff );

	fgets(buff, 255, (FILE*)fp);
	printf("2: %s\n", buff );

	fgets(buff, 255, (FILE*)fp);
	printf("3: %s\n", buff );
	fclose(fp);
}