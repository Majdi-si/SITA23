#include "mesfonctions.h"
#include <stdio.h>
#include <string.h>

/********************************************/
/* affiche à l'écran l'ensemble des caractéristiques des wagons */
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
/*  calcule la somme des pax de tous les wagons de type VOITURE */
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

/****************************************************/
/*  calcule la somme des charges totales des wagons de type MARCHANDISE */
int calculerChargeTotalTrain(int index, wagon *train)
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
/* ajoute à la fin du tableau un nouveau wagon */
void ajouterWagon(char *type,int ident, int data ,int *index,wagon *train)
{
if ( *index < NBMAXWAGONS)
{
    strcpy(train[*index].type,type);
    train[*index].ident=ident;
    train[*index].data=data;
    (*index) ++;
}
else
    fprintf(stderr,"tableau complet...ajouterwagon\n");
}

/**************************************************/
/*  écrit dans le fichier l'ensemble des caractéristiques de chaque wagon du tableau */
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
/*   récupère du fichier l'ensemble des caractéristiques de chaque wagon pour remplir le tableau */
void chargerTrain(char * nomfic, int *index, wagon * train)
{
FILE *fic=fopen(nomfic,"r");
if (fic)
{
    int i=0;
    wagon w;
    while (fscanf (fic, "%s %d %d\n", w.type,&w.ident,&w.data ) >= 2)
    {
        if ( strcmp(w.type,"LOCOMOTIVE")==0)
			w.data=0;
		train[i]=w;
        i++;
    }
    (*index)=i;
    fclose(fic);
}
else
    fprintf(stderr,"pb chargerTrain ouverture fichier %s\n", nomfic);
}
