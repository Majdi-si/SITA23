#include <stdio.h>
#include <stdlib.h>
#include "mesfonctions.h"

int main()
{
    wagon *train=NULL; // variable pour construire le tableau dynamique de wagons
    int index=0; // nombre de wagons du tableau dynamique

    chargerTrainDyn("montrain.txt", &index, &train);
    afficherTrain(index, train);
    printf("nb pax=%d\n", calculerNbPaxTrain(index, train));
    printf("charge total=%d\n", calculerChargeTotaleTrain(index, train));
    ajouterWagonDyn("VOITURE" , 1001, 100,&index,&train);
    sauverTrain("montrain.txt",index, train);
    libererTrain(&index, &train);
    return 0;
}
