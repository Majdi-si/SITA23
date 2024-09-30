#include <stdio.h>
#include <ctype.h>
#include "mesfonctions.h"

void partie1();
void partie2();

int main()
{
    partie1();
    /*partie2();*/
    return 0;
}

/***************************/
void partie1()
{
    Avion t[NBMAX];
    int nb=0;
    char rep='a';
    char nom[50];

    while (toupper(rep) != 'Q')
    {
        printf("        MENU\n");
        printf("\tsaisir S\n");
        printf("\tafficher A\n");
        printf("\tcalculer Occupation O\n");
        printf("\tcharger C\n");
        printf("\tsauver V\n");
        printf("\tquitter Q\n");
        printf("votre choix:");
        rep=getchar();
        getchar();
        switch(toupper(rep)) {
            case 'S': saisir(&nb, t);break;
            case 'A': afficher(nb,t);break;
            case 'C':
                printf("nom du fichier :");
                scanf("%50[^\n]",nom);
                getchar();
                charger(&nb, t, nom);
                break;
            case 'V':
                printf("nom du fichier :");
                scanf("%50[^\n]",nom);
                getchar();
                sauver(nb, t, nom);
                break;
            case 'O': calculerOccupation(nb,t); break;
            case 'Q': printf("au revoir...\n");break;
            default: printf("choix invalide...\n");
        }
    }
}

/****************************/
void partie2()
{
    Avion *t=NULL;
    int nb=0;
    char rep='a';

    while (toupper(rep) != 'Q')
    {
        printf("        MENU\n");
        printf("\tsaisir S\n");
        printf("\tafficher A\n");
        printf("\tcalculerOccupation O\n");
        printf("\tlib�rer L\n");
        printf("\tquitter Q\n");
        printf("votre choix :");
        rep=getchar();
        getchar();
        switch(toupper(rep)) {
            case 'S': saisirDyn(&nb, &t); break;
            case 'A':afficher(nb,t); break;
            case 'O': calculerOccupation(nb,t); break;
            case 'L': liberer(&nb,&t);break;
            case 'Q':printf("au revoir...\n");
        }
    }
}
