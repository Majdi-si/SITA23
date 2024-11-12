#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gp.h"

/***************************************************/
/* chargement des données sur les pilotes dans le tableau dynamique de
/* structures Pilote
*/
void chargerPilotes(int * nbp,Pilote **pilotes,char * nomfichier)
{
    FILE *fic=NULL;
    fic=fopen(nomfichier,"r");
    if (fic)
        {
        int i=0;
        char chaine[100];
        // lecture ligne par ligne dans le fichier
        while (fgets(chaine,100,fic)!=NULL)
            {
             // allocation des structures une par une :
                *pilotes=realloc(*pilotes,sizeof(Pilote)*(i+1));
                //transfert des informations de la ligne dans chacun des champs de la structure :
                sscanf(chaine,"%s %s %d", (*pilotes)[i].nom, (*pilotes)[i].prenom, & (*pilotes)[i].numero);
                (*pilotes)[i].nbPoints=0;
                i++;
            }
        // mise à jour du nombre de structures du tableau
        *nbp=i;
        fclose(fic);
        }
    else
        printf("erreur ouverture fichier %s\n",nomfichier);

}

/**************************************************/
void afficherPilotes(int nbp,Pilote *pilotes)
{
  int i;
    printf(" voici la liste des pilotes :\n");
    for (i=0;i<nbp;i++)
        {
        printf("nom:%s  prenom:%s  numero:%d  nbp:%d\n", pilotes[i].nom,pilotes[i].prenom,pilotes[i].numero,pilotes[i].nbPoints);
        }
    printf("fin affichage\n");
}

/**************************************************/
void chargerCourses(int *nbc,Course **courses,char * nomfichier)
{
    FILE * fic=fopen(nomfichier,"r");
    if (fic)
    {
        int i=0;
        char chaine[100];
        while (fgets(chaine,100,fic)!=NULL)
            {

		// allocation une par une des structures du tableau de Course :
                *courses=realloc(*courses,sizeof(Course)*(i+1));
                // transfert des informations de la ligne dans chacun des champs :
                sscanf(chaine,"%s %d %d %d %d %d %d %d %d %d %d", (*courses)[i].nom, &(*courses)[i].listePilotes[0],
                 &(*courses)[i].listePilotes[1],&(*courses)[i].listePilotes[2],&(*courses)[i].listePilotes[3],
                 &(*courses)[i].listePilotes[4],&(*courses)[i].listePilotes[5],&(*courses)[i].listePilotes[6],
                 &(*courses)[i].listePilotes[7],&(*courses)[i].listePilotes[8],&(*courses)[i].listePilotes[9]);
                i++;
            }
        *nbc=i;
        fclose(fic);

    }
    else
        printf("pb ouverture fichier %s",nomfichier);
}

/**************************************************/
void afficherCourses(int nbc,Course *courses)
{
    int i;
    printf(" voici la liste des courses :\n");
    for (i=0;i<nbc;i++)
        {
        printf("nom de la course:%s\n", courses[i].nom);
        printf("\tnumeros des pilotes : ");
        // affichage des numéros des pilotes selon le classement :
        for (int j=0;j<10;j++)
            printf("%d ",courses[i].listePilotes[j]);
        printf("\n");
        }
    printf("fin affichage\n");

}

/***************************************************/
/* tableau des attributions de points selon le classement :
*/
void initPointsClassement(int **tabclas)
{
    int i;
    // stockage du nombre de points selon le classement dans un tableau local :
    int t[]={26,18,15,12,10,8,6,4,2,1};
    // allocation du tableau dynamique du main ici :
    *tabclas=malloc(sizeof(int)*10);
    // transfert des valeurs des points à attribuer dans le tableau dynamique du main :
    for (i=0;i<10;i++)
        (*tabclas)[i]=t[i];
}

/***************************************************/
void calculerPointsPilotes(int nbp,Pilote *pilotes,int *tabclas,int nbc,Course *courses)
{
    int i;
    // on parcourt chaque course :
    for (i=0;i<nbc;i++)
    {
        //on parcourt les pilotes classés :
        for (int j=0;j<10;j++)
        {
            // on récupère le numéro du pilote courant :
            int num=courses[i].listePilotes[j];
            // on recherche ce pilote parmi la liste des pilotes :
            for (int k=0;k<nbp;k++)
            {
                if (num == pilotes[k].numero)
                {
                    // on ajoute les points à ce pilote :
                    pilotes[k].nbPoints+=tabclas[j];
                }
            }
        }
    }
}

/******************************************************/
void sauverPilotes(int nbp,Pilote *pilotes,char * nomfichier)
{
    FILE *fic=NULL;
    fic=fopen(nomfichier,"w");
    if (fic)
    {
        // tri à bulle :
        int i,j;
        for (i=0;i<nbp;i++)
        {
            for (j=nbp-1;j>i;j--)
            {
                if (pilotes[j].nbPoints > pilotes[j-1].nbPoints)
                    {
                        Pilote temp=pilotes[j];
                        pilotes[j]=pilotes[j-1];
                        pilotes[j-1]=temp;

                    }
            }
        }

	// écriture dans le fichier des données de chaque pilote :
        for (int i=0;i<nbp;i++)
            fprintf(fic,"%s %s %d %d\n",pilotes[i].nom,pilotes[i].prenom,pilotes[i].numero,pilotes[i].nbPoints);
    }
    else
        printf("erreur ouverture fichier %s\n",nomfichier);
}

/***************************************************************/
void liberer(int *nbp,Pilote **pilotes,int *nbc,Course **courses,int **tabclas)
{
    if (*nbp)
    {
        *nbp=0;
        free(*pilotes);
    }
    if (*nbc)
    {
        *nbc=0;
        free(*courses);
    }
    free(*tabclas);
}
