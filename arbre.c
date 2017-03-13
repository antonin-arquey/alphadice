#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"


struct SCell{
	Data Value;
	SCell *Fils;
	int nbFils;
};

struct SArbre{
	SCell *Head;
};

SArbre* CreateArbre(int taille){
	SArbre *arbre = malloc(sizeof(SCell));
	SCell *newCell = malloc(sizeof(SCell));

	SCell listeFils[taille];

	newCell->nbFils = taille;
	newCell->Fils = listeFils;
	newCell->Value = 12;

	arbre->Head = newCell;
	return arbre;
}

SCell* headOfArbre(SArbre *arbre){
	return arbre->Head;
}

SCell* getFils(SCell *cell, int numero){
	return (cell->Fils) + numero;
}

void DeleteArbre(SArbre *arbre){
	free(arbre);
}

void AddElement(SCell *cell, Data *elem, int nbElement){
	SCell *newCells = malloc(sizeof(SCell)*nbElement);
	cell->Fils = newCells;
	cell->nbFils = nbElement;

	for(int i = 0; i < nbElement; i++){
		newCells->Value = *elem;
		newCells++;
		elem++;
	}
}

int sub(SCell *cell, int niv, int tab[],int taille){
	//printf("%d\n",niv);
	if (niv == 0){
		return 0;
	}
	niv--;
	SCell *fils;
	for(int i = 0; i < taille; i++){
		fils = getFils(cell,i);
		AddElement(fils,tab,taille);
		sub(fils,niv,tab,taille);
	}
	return 1;
}

void creation(SArbre *arbre, int niveau){
	int tab[10] = {45,2};
	SCell *head = headOfArbre(arbre);
	AddElement(head,tab,2);
	sub(head,--niveau,tab,2);
}
/*
SCell* AddElementEnd(SArbre *arbre,Data elem){
	SCell *newCell = malloc(sizeof(elem));

	newCell->Value = elem;
	newCell->suivant = NULL;

	if(arbre == NULL){
		arbre->Head = newCell;
		return newCell;
	}
	SCell *temp = arbre->Head;
	while(temp->suivant != NULL){
		temp = temp->suivant;
	}
	temp->suivant = newCell;
	return newCell;
}

SCell* AddElementAfter(SArbre *arbre,SCell *cell,Data elem){
	SCell *newCell = malloc(sizeof(elem));

	newCell->Value = elem;
	if(arbre->Head == NULL){
		arbre->Head = newCell;
		newCell->suivant = NULL;
		newCell->precedent = NULL;
		return newCell;
	}

	newCell->precedent = cell;
	newCell->suivant = cell->suivant;
	cell->suivant = newCell;

	return newCell;
}

void DeleteCell(SArbre *arbre,SCell *cell){
	if(arbre->Head == NULL){
		return;
	}
	SCell *temp = arbre->Head;
	SCell *last;
	while(temp != cell && temp->suivant != NULL){
		last = temp;
		temp = temp->suivant;
	}
	temp->suivant->precedent = last;
	last->suivant = temp->suivant;
	free(cell);
}

SCell* GetFirstElement(SArbre *arbre){
	if(arbre == NULL){
		return NULL;
	}
	return arbre->Head;
}

SCell* GetLastElement(SArbre *arbre){
	if(arbre == NULL){
		return NULL;
	}
	return arbre->Head->precedent;
}

SCell* GetPrevElement(SCell *cell){
	return cell->precedent;
}

SCell* GetNextElement(SCell *cell){
	return cell->suivant;
}
*/
Data getData(SCell *cell){
	if(cell != NULL){
		return cell->Value;
	}
	return NULL;
}
