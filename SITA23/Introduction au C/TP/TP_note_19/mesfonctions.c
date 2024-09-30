#include "mesfonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************/
/*  saisie clavier des caract�ristiques d'un avion � la fin du tableau statique */
void saisir( int *nb, Avion *t)
{

}

/*******************************/
/*  saisie clavier des caract�ristiques d'un avion : ajout dans le tableau dynamique
    par agrandissement */
void saisirDyn( int *nb, Avion **t)
{
	
 }
/*********************************/
/*  affiche pour chaque avion du tableau son taux d'occupation, cad rapport de nombre de resa sur
le nombre de places */
void calculerOccupation(int nb,Avion *t)
{
    
}

/******************************************/
/* chargement dans le tableau statique des avions � partir du fichier texte  */
void charger(int *n, Avion *t, char *nomfichier)
{
  
}

/**********************************/
/* affichage des caract�ristiques de chaque avion du tableau � l'�cran */
void afficher(int nb, Avion *t)
{
    
}

/**********************************/
/*  sauvegarde dans un fichier texte des caract�ristiques de chaque avion (une ligne par avion) */
void sauver(int nb, Avion *t,char * nomfichier)
{


}

/**********************************/
/* lib�ration m�moire du tableau dynamique */
void liberer(int *nb, Avion **t)
{

}
