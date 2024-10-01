#ifndef _ANNUAIRE_H
#define _ANNUAIRE_H

//#include <stdlib.h>
#include "halloc.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h> // pour la fonction toupper()

#define NB_MAX 500

typedef struct {
	char nom[20];
	char prenom[20];
	char tel[12];
	} personne;

typedef personne *  tableau[NB_MAX]; // permet de définir le nouveau type "tableau"

/* fonction affichant les options offertes par le menu à l'utilisateur */
void afficherMenu();

/* fonction du menu principal */
void menu(int *ind,tableau t);

/*fonction de chargement du fichier en mode texte*/
void chargerFichierTexte(int *index,tableau t,char* nomfichier);

/*fonction sauvegardant les données dans un fichier texte*/
void sauverFichierTexte(int index,tableau t,char* nomfichier);

/* fonction de saisie des personnes */
void saisirPersonne(int *index,tableau t);

/* fonction de suppression des personnes */
void supprimerPersonne(int *index, tableau t);

/*fonction d'édition de toutes les personnes */
void editerAnnuaire(int index,tableau t);

#endif
