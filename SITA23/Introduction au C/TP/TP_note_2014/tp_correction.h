#ifndef _TP_CORRECTION_H
#define _TP_H
#define MAX 1000
// structure utilisée pour mémoriser un coureur arrivé :
typedef struct {
    char nom[30]; // nom du coureur
    int dossard;  // numéro de dossard du coureur
    int temps[3];  // temps à l'arrivée : temps[0] en heures, temps[1] en minutes, temps[2] en secondes
}coureur;

// liste des fonctions à développer :

void saisircoureur(int *n,coureur course[]);
void affichercourse(int n,coureur course[]);
void sauvegardercourse(int n,coureur course[], char * nomfic);
void trier(int n,coureur *course);

#endif