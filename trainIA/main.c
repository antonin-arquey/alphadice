#include <stdio.h>
#include <stdlib.h>

double random(){
    return 2 * (rand() / (RAND_MAX + 1.)) - 1;
}

void init(double w[][1], int taille){
  for (int i = 0; i < taille; i++) {
    w[i][0] = random();
  }
}
void recupXY(double X[][3], double Y[][1], double data[][4], int debut, int fin){
  for (int i = debut; i < fin; i++) {
    Y[i][1] = data[i][4];
    for (int h = 0; h < 4; h++){
      X[i][h] = data[i][h];
    }
  }
}

void affichage(double tab[][3], int a, int b){
  printf("--affichage du tableau --\n");
  for(int i = 0; i < a; i++){
    for(int j = 0; j < b; j++){
      printf("%f ", tab[i][j]);
    }
    printf("\n");
  }
  printf("-- fin d'affichage --\n");
}
void dot(double out[][1], double x[][3], double w[][1], int taille){
  double val = 0;
  for (int i = 0; i < taille; i++) {
    for (int j = 0; j < 3; j++) {
      val += x[i][j] * w[j][0];
    }
    out[i][0] = val;
    val = 0;
  }
}
void diff(double err[][1], double y[][1], double out[][1], int taille){
  for (int i = 0; i < taille; i++) {
    err[i][0] = y[i][0] - out[i][0];
  }
}

void transpose(double outT[1][5], double out[5][1]){
    for (int i = 0; i < 5; i++) {
      outT[0][i] = out[i][0];
    }
}

int main(int argc, char const *argv[]) {
  double data[5][4] = {{0,1,3,0},
                     {3,1,0,1},
                     {0,1,0,1},
                     {-2,0,2,0},
                     {5,3,1,0}};

  double trainX[5][3];
  double trainY[5][1];
  recupXY(trainX,trainY,data, 0, 5);
  affichage(trainX, 5, 3);
  double weights[3][1];
  double out[5][1];
  init(weights, 3);

  for(int j = 0; j < 1; j++){
    dot(out, trainX, weights, 5);

    printf("%f %f %f\n", weights[0][0], weights[1][0], weights[2][0]);
    printf("%f %f %f %f %f\n", out[0][0], out[1][0], out[2][0], out[3][0], out[4][0]);

    diff(err, trainY, out, 5);

    //err_delta = err * deriv(out)

    transpose(outT, out);
    dot(update, outT, err, 5);//pas err normalement mais err_delta
    add(weights,update);
  }
  return 0;
}
