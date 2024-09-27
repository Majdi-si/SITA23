#include "annuaire.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <errno.h>  

#define NB_MAX 500


int main (){
    char nomfic[]="personne.txt"; // nom du fichier que l'on va essayer d'ouvrir : il ne doit pas exister.

    /* On réinitialise errno avant d'appeler la fonction susceptible d'engendrer une erreur */
    errno = 0;

    FILE *fic=fopen(nomfic,"r");
    personne* tab = NULL;
    int index = 0;

     if (errno != 0)
    {
        /* Il y a eu une erreur ! */
        fprintf(stderr, "Impossible d'ouvrir le fichier '%s' : '%s'\n",nomfic, strerror(errno));
        //perror("Impossible d'ouvrir ce fichier");
    }
    else
    {
        printf("ouverture en lecture réussie\n quel coup de bol!\n");

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
        ecrire_fichier(nomfic, &tab, &index);
        free(tab);
        
    }
    fclose(fic);
    printf("FIN\n");

    return 0;
}