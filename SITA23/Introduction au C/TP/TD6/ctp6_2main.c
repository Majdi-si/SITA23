#include <stdio.h>
#include <stdlib.h>
#include "ctp6_2.h"
#include <string.h>

#define TAILLEMAX 300

int main(int argc,char * argv[])
{
    char *chaine=NULL;
    char *nomfic=NULL;
    if (argc > 1)  // l'utilisateur a tapé normalement le nom du fichier en plus de la commande
    {
        // le nom du fichier est stocké dans : argv[1]
        if (strlen(argv[1])<TAILLEMAX)
            {
                nomfic=(char*)calloc(strlen(argv[1])+1,sizeof(char));
                strcpy(nomfic,argv[1]);
            }
        else
            {
                printf("pb de nom du fichier (>%d\n",TAILLEMAX);
                return 1;
            }

    }
    else // pas de nom de fichier tapé lors de la commande : on l'impose à "fic.txt"
    {
        nomfic=(char*)calloc(8,sizeof(char));
        strcpy(nomfic,"fic.txt");
    }
    printf("TAPER UNE CHAINE DE CARACTERES : ('\\n' POUR FINIR) ");
    saisir_chaine(&chaine);
    printf("\n");
    ecrire_fichier(nomfic,chaine);
    printf("CONTENU DU FICHIER %s :\n",nomfic);
    afficher_fichier(nomfic);
    free(chaine);
    chaine=NULL;
    return 0;
}

