#include "annuaire.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 


#define NB_MAX 500


int main (){
    personne* tab = NULL;
    int index = 0;
    char rep;
    do {
        afficherMenu();
        rep = toupper(getchar());
        getchar();
        switch (rep) {
            case 'A': saisirPersonne(&index, &tab); break;
            case 'S': supprimerPersonne(&index, &tab); break;
            case 'V': editerAnnuaire(&index, &tab); break;
            case 'Q': break;
        }
    } while (rep != 'Q');
    free(tab);
    return 0;
}