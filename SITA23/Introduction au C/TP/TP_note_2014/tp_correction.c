#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_correction.h"

/********************************************************/
/* fonction qui saisit au clavier un coureur arrivé : son nom, son dossard, son temps.
    Le premier paramètre est un pointeur sur le nombre de coureurs avant la saisie.
    Le deuxième paramètre est le tableau des coureurs.

*/
void saisircoureur(int * ptn, coureur course[MAX])
{
    char temp[20];

    if (*ptn < MAX-1)
        {
            printf("nom du coureur :");
            scanf("%30[^\n]",course[*ptn].nom);
            printf("numéro de dossard :");
            scanf("%d",& course[*ptn].dossard);
            printf("temps du coureur:");
            scanf("%20s",temp);
            sscanf(temp,"%d:%d:%d", & course[*ptn].temps[0],& course[*ptn].temps[1],& course[*ptn].temps[2] );
            (*ptn)++;
        }
    else
        {
            printf(" tableau plein!!!");
        }

}

/********************************************************/
/* La fonction parcourt les n coureurs du tableau et affiche les données de chaque coureur sur une ligne :
        Exemple :
        "nom:toto dossard:1 temps:01:20:08"

        Pour afficher les heures, minutes et secondes, on pourra utiliser le formatage suivant dans un printf :
        "%02d:%02d:%02d"
        Le format "%02d" permet d'afficher un entier sur deux caractères, en complétant à gauche par des zéros si nécessaire.
*/
void affichercourse(int n,coureur course[MAX])
{
    int i=0;
    if (n != 0 )
    {
      printf("\nvoici la liste des coureurs arrivés :\n");
      while (i<n)
        {
            printf("nom: %s  dossard: %d  temps: %02d:%02d:%02d\n",course[i].nom,course[i].dossard, course[i].temps[0],course[i].temps[1],course[i].temps[2]);
            i++;
        }
    }
    else
        {
            printf("\n aucune arrivée ....");
        }

}

/********************************************************/
/* La fonction permet de sauvegarder dans un fichier texte les données du tableau.
Le premier paramètre sera le nombre de coureurs, le deuxième paramètre le tableau de coureurs,
le troisième paramètre sera le nom physique du fichier.
On écrira les données d'un coureur sur une ligne du fichier.
Exemple :
"nom: toto dossard:1 temps:01:20:08"
*/
void sauvegardercourse(int n,coureur course[], char * nomfic)
{
    FILE *fic;

    if (strcmp(nomfic,"") ==0)
        {

            printf("\nNom du fichier incorrecte:");
        }
	else 
		{
		if ((fic=fopen(nomfic,"w")) != NULL)
			{
				int i=0;
				while (i<n)
					{
						fprintf(fic,"nom:%s dossard:%d temps:%02d:%02d:%02d\n",course[i].nom,course[i].dossard,
								course[i].temps[0],course[i].temps[1],course[i].temps[2]);
						i++;
					}
				fclose(fic);
			}

		else
			printf("\npb ouverture fichier : %s\n", nomfic);
		}
}



/************************************
La fonction réalise un tri à bulle sur le tableau, en utilisant le champ temps
comme clé de tri.
On pourra convertir le temps total de chaque coureur en secondes pour comparer deux coureurs.
*/
void trier(int n,coureur *course)
{
    int i,j,k;
    int permut=0;
    for(i=0;i<n && permut;)
        {
            permut=0;
            k=i;
            for(j=n-1;j>k;j--)
                {
                    if (inf(course[j].temps,course[j-1].temps))
                        {
                            coureur c=course[j];
                            course[j]=course[j-1];
                            course[j-1]=c;
                            permut=1;
                            k=j;
                        }
                }
            i=k;
        }
}

/* fonction qui retourne vrai si le premier temps est inférieur au second.
Le temps est stocké dans un tableau de 3 entiers:
    t1[0]: nombre d'heures.
    t1[1]: nombre de minutes.
    t1[2]: nombre de secondes.
*/
int inf(int t1[],int t2[])
{
    int s1= t1[0]*3600+t1[1]*60+t1[2];
    int s2= t2[0]*3600+t2[1]*60+t2[2];;
    return s1<s2;

}