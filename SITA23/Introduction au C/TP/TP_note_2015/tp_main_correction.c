#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_correction.h"

int main()
{
    // déclaration des variables :
    // on utilise un tableau de MAX structures Apt :
    TableauApt tableau;

    // initialisation du tableau
    initApt(tableau);

    // nom du fichier de sauvegarde et de chargement :
    char nomfichierApt[]="fichierApt.txt";

    // variable choix du menu :
    int choix=1;

    // boucle de traitement :
    while (choix !=0)
        {
            printf(" ********* Menu **********\n");
            printf(" 0 : quitter.\n");
            printf(" 1 : saisir un aeroport.\n");
            printf(" 2 : afficher les aeroports.\n");
            printf(" 3 : sauvegarder tous les aeroports.\n");
            printf(" 4 : trier les aeroports par nombre de pistes croissant.\n");
            printf("\n");
            scanf("%d",&choix);
            getchar();
            switch(choix)
            {
                case 0 : break;
                case 1 : saisirApt(tableau);
                    break;
                case 2 : afficherApt(tableau);
                    break;
                case 3 : sauvegarderApt(tableau, nomfichierApt);
                    break;
                case 4 : trierApt(tableau);
                    break;
                default : printf("\n choix invalide, recommencez....");
            }
        }
    return 0;
}



