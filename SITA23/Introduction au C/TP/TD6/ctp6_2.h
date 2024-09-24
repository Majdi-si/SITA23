
#ifndef __CTP6_2_H
#define __CPT6_2_H

#include <stdio.h>

/* fonction affichant le contenu d'un fichier texte à l'écran */
void afficher_fichier(char * nomfic);

/* fonction écrivant le contenu du deuxième paramètre dans un fichier texte */
void ecrire_fichier(char * nomfic, char * texte);

/****************************/
/* fonction qui saisit au clavier une chaîne de longueur quelconque,
    ==> réservation dynamique de la chaîne
    Fonction déjà vue.
*/
int saisir_chaine(char * *ch);

#endif
