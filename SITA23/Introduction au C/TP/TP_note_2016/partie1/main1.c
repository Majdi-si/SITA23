#include <stdio.h>
#include <stdlib.h>
#include "mesfonctions.h"

int main()
{
    wagon train[NBMAXWAGONS]; // NBMAXWAGONS à définir dans le fichier "mesfonctions.h"
    int index=0;    // nombre de structures utilisés du tableau

    chargerTrain("montrain.txt", &index, train);
    afficherTrain(index, train);
    printf("nb pax=%d\n", calculerNbPaxTrain(index, train));
    printf("charge total=%d\n", calculerChargeTotaleTrain(index, train));
    ajouterWagon("VOITURE" , 1001, 100,&index,train);

    sauverTrain("montrain.txt",index, train);
    return 0;
}
