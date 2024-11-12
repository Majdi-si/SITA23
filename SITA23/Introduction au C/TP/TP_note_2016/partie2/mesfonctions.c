#include "mesfonctions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void afficherTrain(int index,wagon * train)
{
    int i;
    for (i=0;i<index ;i++)
    {
        if (strcmp(train[i].type, "VOITURE")==0)
            printf("wagon %d : type=%s nbpax=%d\n",train[i].ident, train[i].type, (int)train[i].data);
        else
            if (strcmp(train[i].type, "LOCOMOTIVE")==0)
                printf("wagon %d : type=%s \n",train[i].ident, train[i].type);
            else
                printf("wagon %d : type=%s charge=%d\n",train[i].ident, train[i].type, train[i].data);


    }

}

/**********************************************/
int calculerNbPaxTrain(int index, wagon *train)
{
int i,somme=0;
    for (i=0;i<index ;i++)
    {
        if (strcmp(train[i].type , "VOITURE")==0)
            somme += train[i].data;
    }
return somme;
}
/***********************************************/
int calculerChargeTotaleTrain(int index, wagon *train)
{
int i;
int somme=0;
    for (i=0;i<index ;i++)
    {
        if (strcmp(train[i].type, "MARCHANDISE")==0)
            somme += train[i].data;
    }
return somme;

}
/**************************************************/
/* ajoute � la fin du tableau un nouveau wagon : r�allocation dynamique pour agrandir */
void ajouterWagonDyn(char *type,int ident, int data ,int *index,wagon **train)
{
    *train = (wagon *)realloc(*train, (*index + 1) * sizeof(wagon));
    if (*index >= NBMAXWAGONS) {
        printf("Nb wagons plein.\n");
        return;
    }

    strcpy((*train)[*index].type, type);
     (*train)[*index].ident = ident;
     (*train)[*index].data = data;

    (*index)++;

}
/**************************************************/
void sauverTrain(char * nomfic,int index, wagon *train)
{
FILE *fic=fopen(nomfic,"w");
if (fic)
{
    int i;
    for (i=0;i<index ;i++)
    {
        if (strcmp( train[i].type,"LOCOMOTIVE")==0)
            fprintf(fic,"%s %d\n",train[i].type, train[i].ident );
        else
            fprintf(fic,"%s %d %d\n",train[i].type, train[i].ident ,train[i].data );
    }
    fclose(fic);
}
else
    fprintf(stderr,"pb sauverTrain ouverture fichier %s\n", nomfic);

}
/**************************************************/
void chargerTrainDyn(char * nomfic, int *index, wagon ** train)
{
    errno = 0;
    FILE *fic=fopen(nomfic,"r");
    if (errno != 0)
    {
        printf("Erreur d'ouverture du fichier %s: %s\n", nomfic, strerror(errno));
        return;
    }
    else{
        int i=0;
        char chaine[40];
        // lecture ligne par ligne dans le fichier
        while (fgets(chaine,40,fic)!=NULL)
            {
             // allocation des structures une par une :
                *train=realloc(*train,sizeof(wagon)*(i+1));
                //transfert des informations de la ligne dans chacun des champs de la structure :
                sscanf(chaine,"%s %d %d ", (*train)[i].type, & (*train)[i].ident, & (*train)[i].data);
                i++;
            }
        *index=i;
    }
    fclose(fic);
}

/****************************************************/
void libererTrain(int *index, wagon **train)
{

    if(*train != NULL){
        free(*train);
        *train = NULL ;
        *index = 0;
    }


}
