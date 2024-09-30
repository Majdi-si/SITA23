#include "mesfonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************/
/*  saisie clavier des caract�ristiques d'un avion � la fin du tableau statique */
void saisir( int *nb, Avion *t)
{
 if (*nb < NBMAX)
 {
      // on remplit la structure au rang donn� par *nb   :
      printf("indicatif :");
      scanf("%20s", t[*nb].indicatif);
      printf("marque :");
      scanf("%20s", t[*nb].marque);
      printf("type :");
      scanf("%20s", t[*nb].type);
      printf("nbplaces :");
	// saisie d'un entier : on utilise le &
      scanf("%d", & t[*nb].nbplaces);
      printf("nbresa :");
      scanf("%d", & t[*nb].nbresa);
	// on incr�mente le nombre de structures
      (*nb)++;
      getchar();
 }
}

/*******************************/
/*  saisie clavier des caract�ristiques d'un avion : ajout dans le tableau dynamique
    par agrandissement */
void saisirDyn( int *nb, Avion **t)
{
	// on alloue un tableau plus grand : *nb+1      
	Avion * newt=realloc(*t,sizeof(Avion) * (*nb +1));
      if (newt) // agrandissement r�ussi
      {
        *t=newt; // on r�cup�re l'adresse du tableau agrandi
        printf("indicatif :");
        scanf("%20s", (*t)[*nb].indicatif);
        printf("marque :");
        scanf("%20s", (*t)[*nb].marque);
        printf("type :");
        scanf("%20s", (*t)[*nb].type);
        printf("nbplaces :");
        scanf("%d", & (*t)[*nb].nbplaces);
        printf("nbresa :");
        scanf("%d", & (*t)[*nb].nbresa);
        (*nb)++;
        getchar();
      }
      else
        printf("pb realloc !!!");
 }
/*********************************/
/*  affiche pour chaque avion du tableau son taux d'occupation, cad rapport de nombre de resa sur
le nombre de places */
void calculerOccupation(int nb,Avion *t)
{
    int i=0;
    for(i=0;i<nb;i++)
    {
	// l'op�rateur / retourne une valeur r�elle si au moins une des deux op�randes est r�elle : 
	// il faut donc multiplier une des deux par 100.0 (et non 100)
	// il fallait afficher 2 d�cimales : format %.2f        
	printf("%s taux occupation = %.2f%\n",t[i].indicatif, (t[i].nbresa * 100.0) / t[i].nbplaces );
    }
}

/******************************************/
/* chargement dans le tableau statique des avions � partir du fichier texte  */
void charger(int *n, Avion *t, char *nomfichier)
{
    FILE *fic=fopen(nomfichier,"r");
    if (fic)
    {
        char chaine[200];
        int i=0;
	// on lit une ligne jusqu'� la fin du fichier :
        while (fgets(chaine,200,fic) !=NULL && i<NBMAX)
        {
            sscanf(chaine,"%s %s %s %d %d", t[i].indicatif,t[i].marque,t[i].type,
                   &t[i].nbplaces, &t[i].nbresa);
            i++;
        }
        *n=i;
        fclose(fic);
    }
    else
        printf("pb ouverture charger !!!");
}

/**********************************/
/* affichage des caract�ristiques de chaque avion du tableau � l'�cran */
void afficher(int nb, Avion *t)
{
    int i=0;
    for (i=0; i< nb; i++)
    {
        printf("indicatif:%s\n marque:%s\n type:%s\n nbplaces:%d\n nbresa:%d\n", t[i].indicatif, t[i].marque,
              t[i].type, t[i].nbplaces, t[i].nbresa);
    }
}

/**********************************/
/*  sauvegarde dans un fichier texte des caract�ristiques de chaque avion (une ligne par avion) */
void sauver(int nb, Avion *t,char * nomfichier)
{
    FILE *fic=fopen(nomfichier,"w");
    if (fic != NULL)
        {
            int i=0;
            while (i< nb)
            {
                fprintf(fic,"%s %s %s %d %d\n", t[i].indicatif, t[i].marque, t[i].type,
                        t[i].nbplaces, t[i].nbresa);
                i++;
            }

            fclose(fic);
        }
    else
        printf("pb ouverture!!!");

}

/**********************************/
/* lib�ration m�moire du tableau dynamique */
void liberer(int *nb, Avion **t)
{
    if (*t != NULL)
    {
        free( *t);
        *t=NULL;
        *nb=0;
    }
}
