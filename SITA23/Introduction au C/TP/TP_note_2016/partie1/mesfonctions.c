#include "mesfonctions.h"
#include <stdio.h>
#include <string.h>

/********************************************/
/* affiche à l'écran l'ensemble des caractéristiques des wagons */
void afficherTrain(int index, wagon *train)
{
    for (int i = 0; i<index; i++){
        if(strcmp(train[i].type,"LOCOMOTIVE")==0){
            printf("Type : %s\n", train[i].type);
            printf("Identification : %d\n\n", train[i].ident);
        }
        if(strcmp(train[i].type,"VOITURE")==0){
            printf("Type : %s\n", train[i].type);
            printf("Identification : %d\n", train[i].ident);
            printf("Nombre de passagers : %d\n\n", train[i].data);
        }
        if(strcmp(train[i].type,"MARCHANDISE")==0){
            printf("Type : %s\n", train[i].type);
            printf("Identification : %d\n", train[i].ident);
            printf("Charge : %d\n\n", train[i].data);
        }
    }
    
}

/**********************************************/
/* calcule la somme des pax de tous les wagons de type VOITURE */
int calculerNbPaxTrain(int index, wagon *train)
{
    int somme = 0;
    for (int i = 0; i<index; i++){
        if(strcmp(train[i].type,"VOITURE")==0){
            somme += train[i].data;
        }
    }
    return somme;
}

/****************************************************/
/* calcule la somme des charges totales des wagons de type MARCHANDISE */
int calculerChargeTotalTrain(int index, wagon *train)
{
    int somme = 0;
    for (int i = 0; i<index; i++){
        if(strcmp(train[i].type,"MARCHANDISE")==0){
            somme += train[i].data;
        }
    }
    return somme;
}

/**************************************************/
/* ajoute à la fin du tableau un nouveau wagon */
void ajouterWagon(char *type, int ident, int data, int *index, wagon *train)
{
    if (*index < NBMAXWAGONS){
        train[*index].data = data;
        train[*index].ident = ident;
        strcpy(train[*index].type, type);
        (*index)++;
    }
    else{
    fprintf(stderr,"tableau complet...ajouterwagon\n");
    }
}

/**************************************************/
/* écrit dans le fichier l'ensemble des caractéristiques de chaque wagon du tableau */
void sauverTrain(char *nomfic, int index, wagon *train)
{
    // Function body removed
}

/**************************************************/
/* récupère du fichier l'ensemble des caractéristiques de chaque wagon pour remplir le tableau */
void chargerTrain(char *nomfic, int *index, wagon *train)
{
    // Function body removed
}

int main(){
    wagon train[NBMAXWAGONS]; // NBMAXWAGONS à définir dans le fichier "mesfonctions.h"*
    int index=1; // nombre de structures utilisés du tableau
    train->data = 0;
    train->ident = 0;
    ajouterWagon("LOCOMOTIVE", 1, 0, &index, train);
    ajouterWagon("VOITURE", 2, 100, &index, train);
    ajouterWagon("MARCHANDISE", 3, 1000, &index, train);
    afficherTrain(index, train);
    printf("nb pax=%d\n", calculerNbPaxTrain(index, train));
    printf("charge total=%d\n", calculerChargeTotalTrain(index, train));

    return 0;
}