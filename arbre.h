#ifndef _ARBRE_H
#define _ARBRE_H

typedef int Data;
typedef struct SCell SCell;
typedef struct SArbre SArbre;

SArbre* CreateArbre(int taille);
void DeleteArbre(SArbre *arbre);
void AddElement(SCell *cell, Data *elem, int nbElement);

SCell* headOfArbre(SArbre *arbre);
SCell* getFils(SCell *cell, int numero);
void creation(SArbre *arbre, int niveau);
/*SCell* AddElementBegin(SArbre *arbre,Data elem);
SCell* AddElementEnd(SArbre *arbre,Data elem);
SCell* AddElementAfter(SArbre *arbre,SCell *cell,Data elem);
void DeleteCell(SArbre *arbre,SCell *cell);

SCell* GetFirstElement(SArbre *arbre);
SCell* GetLastElement(SArbre *arbre);
SCell* GetPrevElement(SCell *cell);
SCell* GetNextElement(SCell *cell);*/
Data getData(SCell *cell);

#endif
