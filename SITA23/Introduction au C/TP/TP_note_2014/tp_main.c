#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_correction.h"

int main()
{
    // d�claration des variables :
    // on utilise un tableau de MAX coureurs pour stocker les coureurs :
    coureur course[MAX];
    // n : nombre de coureurs arriv�s :
    int n=0;
    // nom du fichier de sauvegarde :
    char nomfichiercourse[]="fichiercourse.txt";
    // variable choix :
    int choix=1;

    // boucle de traitement :
    while (choix !=0)
        {
            printf(" ********* Menu **********\n");
            printf(" 0 : quitter.\n");
            printf(" 1 : saisir une arriv�e.\n");
            printf(" 2 : afficher les coureurs arriv�s.\n");
            printf(" 3 : sauvegarder tous les coureurs arriv�s.\n");
            printf(" 4 : trier les arriv�es.\n");
            printf("\n");
            scanf("%d",&choix);
            getchar();
            switch(choix)
            {
                case 0 : break;
                case 1 : saisircoureur(&n, course);
                    break;
                case 2 : affichercourse(n, course);
                    break;
                case 3 : sauvegardercourse(n,course, nomfichiercourse);
                    break;
                case 4 : trier(n,course);
                    break;
                default : printf("\n choix invalide, recommencez....");
            }
        }
    return 0;
}

