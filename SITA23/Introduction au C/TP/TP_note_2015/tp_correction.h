#ifndef _TP_CORRECTION_H
#define _TP_CORRECTION_H
#define MAX 100
#define INITAPT "XXXX"
// type correspondant à une chaîne de caractères :
typedef char chaine[10];

// structure utilisée pour mémoriser un aéroport :
typedef struct {
    chaine nom; // code OACI de l'aéroport (chaîne de 10 caractères maximum avec le '\0')
    int nbpistes;  // nombre de pistes
    chaine *nomspistes;  // tableau dynamique à allouer contenant le nom de chacune des pistes
} Apt;

// tableau de MAX structures Apt :
typedef Apt TableauApt[MAX];

// liste des fonctions à développer :

// initialisation de chaque case du tableau ( champ nom égal à INITAPT):
void initApt(TableauApt tapt);

// rajoute un aéroport ans le tableau "tapt" par saisie clavier :
void saisirApt(TableauApt tapt);

// affichage des données de chaque aeroport à l'écran :
void afficherApt(TableauApt tapt);

// sauvegarde dans le fichier des données de chaque aeroport du tableau :
void sauvegarderApt(TableauApt tapt, char * nomfic);


// tri du tableau d'aeroport par nombre de pistes croissant :
void trierApt(TableauApt tapt);

#endif
