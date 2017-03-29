typedef struct Matrice Matrice;

double random();

Matrice init_rand(int wx, int wy);
Matrice init0(int wx, int wy);
Matrice addition(Matrice m1, Matrice m2);
Matrice soustraction(Matrice m1, Matrice m2);
Matrice dot(Matrice m1, Matrice m2);
Matrice transpose(Matrice m);

void applyMat(Matrice m, double (*f)(double));
double pow2(double m);

void freeMat(Matrice m);
void affichage(Matrice m);