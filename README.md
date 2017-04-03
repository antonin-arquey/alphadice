# AlphaDice

## Projet de C autour du jeu Dice Wars

### Utilisation

```bash
make
./Alphadice 1 3 ./libIA.so
```
##### Arguments

Premier argument : Nombre de parties (au moins 1)
Second argument : Nombre de joueurs (de 2 à 8)
Arguments suivants : Librairies dynamiques pour les IA

Chaque fichier d'IA gère une IA, le reste des joueurs sont des joueurs humains.

### Principe du jeu

Le jeu se joue au tour par tour.
Chaque joueur possède une couleur et des territoires sur lesquels sont placés jusqu'a 8 dés.
Quand un joueur attaque depuis un des ses territoires un territoire adjacent, un combat de dé est commencé avec le nombre de dés de chaque joueur (disposés sur ces territoires).

### LOG

Ligne 1 : nombre de pays n
n lignes suivantes : idCellule, idOwner, coordX, coordY, nbDices

Symbole /-/ : Debut d'un tour

  idAttaquant, idCelluleFrom, idCelluleTo, ScoreAttack, ScoreDefense

Symbole /// : fin du tour d'un joueur et début de la remise des dé

  idCell (on rajoute un dé a cette cellule)

Symbole ### : ligne apres -> gagnant de la partie (jusqu'au prochain symbole ###)
