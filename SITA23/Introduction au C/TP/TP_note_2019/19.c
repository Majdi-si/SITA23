#include <stdio.h>
#include "19.h"

void saisir (int * nb, Avion * t){
    if ((*nb) < NBMAX ){

        printf("indicactif de l'avion:");
        fscanf("%20s \n", t[*nb].indicatif);
        printf("marque de l'avion:");
        fscanf("%20s \n", t[*nb].marque);
        printf("type de l'avion:");
        fscanf("%20s \n", t[*nb].type);
        printf("nb places de l'avion:");
        fscanf("%d", &t[*nb].nbplaces);
        printf("nb resa de l'avion:");
        fscanf("%d", &t[*nb].nbresa);
        (*nb) ++;
        getchar();
    }

}

void afficher(int nb, Avion * t){

    for (int i = 0; i < nb ; i++){

    
        printf("%20s %20s %20s %d %d", t[i].indicatif, t[i].marque, t[i].type, t[i].nbplaces, t[i].nbresa);
    }
}

void calculerOccupation(int nb, Avion * t){

    for (int i  =0; i< nb ; i++){
        printf("%20s taux d'occupation : %.2f", t[i].indicatif, (t[i].nbresa * 100.0 / t[i].nbplaces));
    }
}

void charger(int *nb, Avion *t, char * nomfichier){

    FILE* fic = fopen(nomfichier, "r");
    if (fic){

        
    }
}