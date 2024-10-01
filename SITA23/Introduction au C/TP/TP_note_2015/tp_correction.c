#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_correction.h"

/********************************************************/
/* fonction qui initialise chaque case du tableau en mettant la valeur "XXXX" au champ nom.*/

void initApt(TableauApt tapt)
{
    int i=0;
    for (i=0;i<MAX;i++)
        strcpy(tapt[i].nom,INITAPT);
}

/********************************************************/
/* fonction qui saisit au clavier un aeroport : son nom, son nombre de pistes et leurs noms.

*/
void saisirApt(TableauApt tapt)
{

    int i=0,j;
    while (i<MAX && strcmp(tapt[i].nom,INITAPT)!=0)
        i++;
    if (i>=MAX)
    {
        printf(" tableau plein \n");
    }
    else
    {
        printf("code aeroport :");
        scanf("%9s",tapt[i].nom);
        printf("nb de pistes :");
        scanf("%d",& tapt[i].nbpistes);
		// on alloue autant de chaine (une chaîne = 10 caractères) que de pistes :
        tapt[i].nomspistes=(chaine*)malloc(sizeof(chaine)*tapt[i].nbpistes);
        for (j=0;j< tapt[i].nbpistes;j++)
        {
           printf("nom de la piste %d :",j);
           scanf("%9s",tapt[i].nomspistes[j]);
        }
    }
}

/********************************************************/
/* la fonction affiche les aéroports stockés dans le tableau : on affichera le nom,
le nombre de pistes et le nom de chacune des pistes de chaque aéroport.
*/
void afficherApt(TableauApt tapt)
{
    int i=0,j;
     printf("\nvoici la liste des aeroports :\n");
    while (i<MAX && (strcmp(tapt[i].nom,INITAPT) !=0))
    {
         printf("nom: %s  nb pistes: %d  \n",tapt[i].nom,tapt[i].nbpistes);
        for (j=0;j< tapt[i].nbpistes;j++)
        {
           printf("nom de la piste %d :%s\n",j,tapt[i].nomspistes[j]);
        }
        i++;
    }
  }

/********************************************************/
/* la fonction sauvegarde dans un fichier texte chacun des aéroports stockés dans le tableau.
On écrira les données d’un aéroport sur une ligne du fichier.
*/
void sauvegarderApt(TableauApt tapt, char * nomfic)
{
    FILE *fic;
    if (strcmp(nomfic,"") ==0)
        {
            printf("\nNom du fichier de sauvegarde incorrecte:");
        }
	else
		{
		if ((fic=fopen(nomfic,"w")) != NULL)
			{
				int i=0,j,n;
				// calcul du nombre d'aéroports dans le tableau :
                for(i=0;i<MAX && (strcmp(tapt[i].nom,INITAPT)!=0);i++) ;
                n=i;
                i=0;
				// on a n aéroports dans le tableau :
				while (i<n)
					{
						fprintf(fic,"%s %d ",tapt[i].nom,tapt[i].nbpistes);
						for (j=0; j< tapt[i].nbpistes;j++)
                            fprintf(fic,"%s ",tapt[i].nomspistes[j]);
                        fprintf(fic,"\n");
						i++;
					}
				fclose(fic);
			}
		else
			printf("\npb ouverture fichier : %s\n", nomfic);
		}
}


/************************************
La fonction réalise un tri par sélection sur le tableau, en utilisant le champ nbpistes
comme clé de tri.
*/
void trierApt(TableauApt tapt)
{
    int i,j,n,min;
    // on calcule le nombre d'aeroports dans le tableau :
    for(i=0;i<MAX && (strcmp(tapt[i].nom,INITAPT)!=0);i++)
		n=i+1;

    for(i=0;i<=n-2;i++)
        {
            min=i;
            for(j=i+1;j<=n-1;j++)
                {
                    if (tapt[j].nbpistes<tapt[min].nbpistes)
                        {
                            min=j;
                        }
                }
            if (min != i)
                {
					// on permute les strucutres i et min :
                    Apt p=tapt[i];
                    tapt[i]=tapt[min];
                    tapt[min]=p;
                }
        }
}
