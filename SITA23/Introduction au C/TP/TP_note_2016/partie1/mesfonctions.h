#ifndef MESFONCTIONS_H_INCLUDED
#define MESFONCTIONS_H_INCLUDED
#define NBMAXWAGONS 1000  // nombre max de wagons du train

typedef struct {
    char type[30] ; // type du wagon : LOCOMOTIVE ou VOITURE ou MARCHANDISE
    int ident;  // identifiant du wagon
    int data;   // nombre de passagers ou charge utile de marchandises selon le type
} wagon;

void afficherTrain(int index,wagon * train);
int calculerNbPaxTrain(int index, wagon *train);
int calculerChargeTotalTrain(int index, wagon *train);
void ajouterWagon(char *type, int ident, int charge ,int *index,wagon *train);
void sauverTrain(char * nomfic,int index, wagon *train);
void chargerTrain(char * nomfic, int *index, wagon * train);

#endif // MESFONCTIONS_H_INCLUDED
