/* structure dynamique et tableaux de structures dynamiques */

#include <stdio.h>
#include <stdlib.h>

// on va définir un nouveau type : structure eleve.
typedef struct {
    char nom[20];
    float note;
    } eleve;

// les deux mêmes fonctions que précédemment :
void saisir_eleve(eleve * e);
void afficher_eleve(eleve e);
// fonction qui réserve en mémoire dynamique un tableau de dim structure eleve :
void reserver_eleve(int dim,eleve **e );
// fonction qui libère le tableau :
void liberer_eleve(eleve **e );

int main()
{
    eleve *moi=NULL;
    eleve *eux=NULL;

    reserver_eleve(1,&moi);
    reserver_eleve(2,&eux);

    saisir_eleve( moi);
    afficher_eleve( *moi);
    liberer_eleve(&moi);

    getchar();
    saisir_eleve( eux);
    getchar();
    saisir_eleve( eux+1);  // idem que : saisir_eleve(& eux[1]);


    afficher_eleve(eux[0]);
    afficher_eleve(eux[1]); // idem que : afficher_eleve( *(eux+1) );
    liberer_eleve(&eux);

    printf("\nPOUR CONTINUER FRAPPER UNE TOUCHE ");
    getchar();
    return 0 ;
}

// ajouter ici les définitions des fonctions déclarées ci-dessus.

