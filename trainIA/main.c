#include <stdio.h>
#include <stdlib.h>


/*Ce code etait destiné à pouvoir analysé un base de données de parties pour ensuite 
  approximer la meilleure fonction d'évaluation des maps au niveau des feuilles del'arbre de recherche
*/

typedef struct{
  double** tab;
  int nbL;  //nombre de lignes
  int nbC;  //nombre de colonnes
}Matrice;

double random(){
    return 2 * (rand() / (RAND_MAX + 1.)) - 1;
}

//on initialise les paramêtres à apprendre de manière aléatoire
Matrice init_rand(int wx, int wy){
  Matrice mat;
  mat.tab = malloc(sizeof(double)*wy);

  for(int i = 0;i<wy;i++){
    mat.tab[i] = malloc(sizeof(double)* wx);
  }

  for (int i = 0; i < wy; i++) {
    for (int j=0; j < wx; j++){
      mat.tab[i][j] = random();
    }
  }

  mat.nbC = wx;
  mat.nbL = wy;

  return mat;
}

//initialisation de la matrice avec des zeros
Matrice init0(int wx, int wy){
  Matrice mat;
  double** w = malloc(sizeof(double)*wy);
  for(int i = 0;i<wy;i++){
    w[i] = malloc(sizeof(double)* wx);
  }

  for (int i = 0; i < wy; i++) {
    for (int j=0; j < wx; j++){
      w[i][j] =0;
    }
  }

  mat.tab = w;
  mat.nbC = wx;
  mat.nbL = wy;
  return mat;
}

//fonction pour faire le produit matriciel
Matrice dot(Matrice m1, Matrice m2){
  Matrice res;
  res = init0(m1.nbL,m2.nbC);
  if (m1.nbC != m2.nbL){
    printf("Les matrices ne peuvent pas être multipliées entre elles (Dimensions non compatibles).\n");
    return res;
  }

  double val=0;
  for (int i = 0; i < m1.nbL; i++) {
    for (int j = 0; j < m1.nbL; j++) {
      val = 0;
      for (int k=0; k< m2.nbL;k++){
        val += m1.tab[i][k] * m2.tab[k][j];
      }
      res.tab[i][j] = val;
    }
    val = 0;
  }

  return res;
}

//fonction pour faire une addition de matrice
Matrice addition(Matrice m1, Matrice m2){
  Matrice m3 = init0(m1.nbC,m1.nbL);

  if((m1.nbL != m2.nbL) || (m1.nbC != m2.nbC)){
    printf("Les matrices ne peuvent pas être additionnés entre elles (Dimensions non compatibles).\n");
    return m3;
  }

  for(int i = 0; i < m1.nbL; i++){
    for(int j = 0; j < m1.nbC; j++){
      m3.tab[i][j]=m1.tab[i][j]+m2.tab[i][j];
    }
  }

  return m3;
}

//fonction pour soustraire 2 matrices
Matrice soustraction(Matrice m1, Matrice m2){
  Matrice m3 = init0(m1.nbC,m1.nbL);

  if((m1.nbL != m2.nbL) || (m1.nbC != m2.nbC)){
    printf("Les matrices ne peuvent pas être soustraites entre elles (Dimensions non compatibles).\n");
    return m3;
  }

  for(int i = 0; i < m1.nbL; i++){
    for(int j = 0; j < m1.nbC; j++){
      m3.tab[i][j]=m1.tab[i][j]-m2.tab[i][j];
    }
  }

  return m3;
}

//fonction pour transposer une matrice
Matrice transpose(Matrice m){
    Matrice r = init0(m.nbL,m.nbC);

    for (int i = 0; i < m.nbL; i++){
      for (int j=0;j<m.nbC;j++){
        r.tab[j][i]=m.tab[i][j];
      }
    }

    return r;
}

//appliquer une fonction à chaque élément de la matrice
void applyMat(Matrice m, double (*f)(double)){
  for (int i = 0; i < m.nbL; i++){
      for (int j=0;j<m.nbC;j++){
        m.tab[i][j]=f(m.tab[i][j]);
    }
  }
}

//fonction pour free les éléments de la matrice
void freeMat(Matrice m){
  for (int i=0;i<m.nbL;i++){
    free(m.tab[i]);
  }
  free(m.tab);
}
/*
void recupXY(double X[][3], double Y[][1], double data[][4], int debut, int fin){
  for (int i = debut; i < fin; i++) {
    Y[i][1] = data[i][4];
    for (int h = 0; h < 4; h++){
      X[i][h] = data[i][h];
    }
  }
}*/

double pow2(double m){
  return m*m;
}

//fonction pour afficher la matrice
void affichage(Matrice m){
  printf("--affichage du tableau --\n");
  for(int i = 0; i < m.nbL; i++){
    for(int j = 0; j < m.nbC; j++){
      printf("%f \t", m.tab[i][j]);
    }
    printf("\n");
  }
  printf("-- fin d'affichage --\n");
}

int main(int argc, char const *argv[]) {
  Matrice m,m2,m3;
  int mx=4;
  int my=3;
  int m2x=3;
  int m2y = 4;
  m = init_rand(mx,my);
  m2 = init_rand(m2x,m2y);
  affichage(m);
  affichage(m2);
  m3 = dot(m,m2);
  affichage(m3);
  applyMat(m3,pow2);
  affichage(m3);

  freeMat(m);
  freeMat(m2);
  freeMat(m3);

  /*double data[5][4] = {{0,1,3,0},
                     {3,1,0,1},
                     {0,1,0,1},
                     {-2,0,2,0},
                     {5,3,1,0}};

  double trainX[5][3];
  double trainY[5][1];
  recupXY(trainX,trainY,data, 0, 5);
  affichage(trainX, 5, 3);
  int weightsX = 0;
  int weightsY = 0;
  double **weights;
  init(weights, weightsX, weightsY);
  double out[5][1];

  for(int j = 0; j < 1; j++){
    dot(out, trainX, weights, 5);

    printf("%f %f %f\n", weights[0][0], weights[1][0], weights[2][0]);
    printf("%f %f %f %f %f\n", out[0][0], out[1][0], out[2][0], out[3][0], out[4][0]);

    diff(err, trainY, out, 5);

    //err_delta = err * deriv(out)

    transpose(outT, out);
    dot(update, outT, err, 5);//pas err normalement mais err_delta
    add(weights,update);
  }*/
  return 0;
}
