#ifndef __MESFONCTIONS__
#define __MESFONCTIONS__
#define NBMAX 10

typedef struct {
    char indicatif[20];
    char marque[20];
    char type[20];
    int nbplaces;
    int nbresa;
} Avion;

void saisir( int *nb, Avion *t);
void saisirDyn( int *nb, Avion **t);
void calculerOccupation(int nb,Avion *t);

void charger(int *n, Avion *t, char *nomfichier);
void afficher(int n, Avion *t);
void sauver(int n, Avion *t,char * nomfichier);
void liberer(int *n, Avion **t);

#endif
