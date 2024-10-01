#ifndef MESFONCTIONS_H_INCLUDED
#define MESFONCTIONS_H_INCLUDED
#define NBMAXWAGONS 1000

typedef struct {
    char type[30] ;
    int ident;
    int data;
} wagon;


void afficherTrain(int index,wagon * train);
int calculerNbPaxTrain(int index, wagon *train);
int calculerChargeTotaleTrain(int index, wagon *train);
void ajouterWagonDyn(char *type, int ident, int charge ,int *index,wagon **train);
void sauverTrain(char * nomfic,int index, wagon *train);
void chargerTrainDyn(char * nomfic, int *index, wagon ** train);
void libererTrain(int *index, wagon **train);

#endif // MESFONCTIONS_H_INCLUDED
