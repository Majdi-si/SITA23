#include "mesfonctions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	// le tableau a une taille actuelle de (*index) cases.
	// on l'agrandit d'une case en plus :
    wagon * newtrain=realloc(*train,sizeof(wagon)*(*index + 1));

if ( newtrain) // allocation r�ussie
{
    *train=newtrain;
    strcpy((*train)[*index].type,type);
    (*train)[*index].ident=ident;
    (*train)[*index].data=data;
    (*index) ++;
}
else
    fprintf(stderr,"allocation impossible...ajouterwagon\n");

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
FILE *fic=fopen(nomfic,"r");
if (fic)
{
    wagon w;
    while (fscanf (fic, "%s %d %d\n", w.type,&w.ident,&w.data ) >= 2)
    {
        // correction version 1 :
		(*index) ++;
        wagon * nt=(wagon*)realloc(*train,sizeof(wagon)* (*index));
        if (nt)
        {
            *train=nt;
            (*train)[(*index)-1]=w;
        }
		// fin correction version 1
		// correction version 2 :
		// ajouterWagonDyn((w.type,w.ident,w.data ,index,train);		
		// fin correction version2
        else
            {
                fprintf(stderr,"pb realloc chargerTrainDyn\n");
                exit(1);
            }
    }
    (*index)=i;
    fclose(fic);
}
else
    fprintf(stderr,"pb chargerTrain ouverture fichier %s\n", nomfic);
}
/****************************************************/
void libererTrain(int *index, wagon **train)
{
    if (*train !=NULL)
    {
        free(*train);
		*train=NULL;
        *index=0;
    }
    else
         fprintf(stderr,"pb tableau � NULL dans libererTrain\n");

}
