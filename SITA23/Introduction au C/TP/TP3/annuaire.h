#include <stdio.h>
#ifndef _ANNUAIRE_H
#define _ANNUAIRE_H
#define MAX 500
#endif

typedef struct {
	char nom[20];
	char prenom[20];
	char tel[12];
	} personne;

void afficherMenu();
void saisirPersonne(int *index, personne **tab);
void supprimerPersonne(int *index, personne **tab);
void editerAnnuaire(int *index, personne **tab);
char* majuscule(char *chaine);
