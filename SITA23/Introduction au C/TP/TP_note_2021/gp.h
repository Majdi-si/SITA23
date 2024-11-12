#ifndef __GP_H
#define __GP_H
#include <stdio.h>

typedef struct {
    char nom[20];
    char prenom[20];
    int numero;
    int nbPoints;
} Pilote;

typedef struct {
    char nom[50];
    int listePilotes[10];
} Course;

void chargerPilotes(int * nbp,Pilote **pilotes,char * nomfichier);
void afficherPilotes(int nbp,Pilote *pilotes);
void chargerCourses(int *nbc,Course **courses,char * nomfichier);
void afficherCourses(int nbc,Course *courses);
void initPointsClassement(int **tabclas);
void calculerPointsPilotes(int nbp,Pilote *pilotes,int *tabclas,int nbc,Course *courses);
void sauverPilotes(int nbp,Pilote *pilotes,char * nomfichier);
void liberer(int *nbp,Pilote **pilotes,int *nbc,Course **courses,int **tabclas);

#endif