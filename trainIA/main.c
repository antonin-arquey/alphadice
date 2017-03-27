#include <stdio.h>
#include <stdlib.h>

double random();
double** init_rand(int wx, int wy);
double** init0(int wx, int wy);
double** addition(double** m1, double** m2, int mx, int my);
void affichage(double **tab, int ax, int ay);
double** soustraction(double** m1, double** m2, int mx, int my);
double** dot(double **a, int ax, int ay, double **b, int bx, int by);

double random(){
    return 2 * (rand() / (RAND_MAX + 1.)) - 1;
}

double** init_rand(int wx, int wy){
  double** w = malloc(sizeof(double)*wy);
  int test;
  for(int i = 0;i<wy;i++){
    w[i] = malloc(sizeof(double)* wx);
  }

  for (int i = 0; i < wy; i++) {
    for (int j=0; j < wx; j++){
      test = (int)(random()*10);
      w[i][j] =(double)(test);
    }
  }

  return w;
}

double** init0(int wx, int wy){
  double** w = malloc(sizeof(double)*wy);
  for(int i = 0;i<wy;i++){
    w[i] = malloc(sizeof(double)* wx);
  }

  for (int i = 0; i < wy; i++) {
    for (int j=0; j < wx; j++){
      w[i][j] = 0;
    }
  }
  return w;
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

void affichage(double **tab, int ax, int ay){
  printf("--affichage du tableau --\n");
  for(int i = 0; i < ay; i++){
    for(int j = 0; j < ax; j++){
      printf("%f \t", tab[i][j]);
    }
    printf("\n");
  }
  printf("-- fin d'affichage --\n");
}

double** dot(double **a, int ax, int ay, double **b, int bx, int by){
  double** r = init0(bx,ay);
  if (ax != by){
    printf("Les matrices ne peuvent pas être multipliées entre elles (Dimensions non compatibles).\n");
    return NULL;
  }

  double val=0;
  for (int i = 0; i < ay; i++) {
    for (int j = 0; j < ax; j++) {
      val += a[i][j] * b[j][i];
      printf("%f * %f +", a[i][j],b[j][i]);
      /*for (int k=0; k< by;k++){
        printf("%f * %f +", a[i][k],b[k][i]);
        //val += a[i][k] * b[k][i];
      }
      r[i][j] = val;*/
    }
    printf("\n");
    val = 0;
  }

  return r;
}

double** addition(double** m1, double** m2, int mx, int my){
  double** r = init0(mx,my);

  for(int i = 0; i < my; i++){
    for(int j = 0; j < mx; j++){
      r[i][j]=m1[i][j]+m2[i][j];
    }
  }

  return r;
}

double** soustraction(double** m1, double** m2, int mx, int my){
  double** r = init0(mx,my);

  for(int i = 0; i < my; i++){
    for(int j = 0; j < mx; j++){
      r[i][j]=m1[i][j]-m2[i][j];
    }
  }

  return r;
}

/*
void transpose(double outT[1][5], double out[5][1]){
    for (int i = 0; i < 5; i++) {
      outT[0][i] = out[i][0];
    }
}*/

int main(int argc, char const *argv[]) {
  double **m,**m2,**m3;
  int mx=3;
  int my=2;
  int m2x=2;
  int m2y = 3;
  m = init_rand(mx,my);
  m2 = init_rand(m2x,m2y);
  affichage(m,mx,my);
  affichage(m2,m2x,m2y);
  m3 = dot(m, mx, my,m2,m2x,m2y);
  affichage(m3,m2x,my);

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
