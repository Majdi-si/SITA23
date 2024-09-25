#ifndef __CTP6_2_H
#define __CPT6_2_H

#include <stdio.h>

/* fonction affichant le contenu d'un fichier texte � l'�cran */
void afficher_fichier(char * nomfic);

/* fonction �crivant le contenu du deuxi�me param�tre dans un fichier texte */
void ecrire_fichier(char * nomfic, char * texte);

/****************************/
/* fonction qui saisit au clavier une cha�ne de longueur quelconque,
    ==> r�servation dynamique de la cha�ne
    Fonction d�j� vue.
*/
int saisir_chaine(char * *ch);

#endif
