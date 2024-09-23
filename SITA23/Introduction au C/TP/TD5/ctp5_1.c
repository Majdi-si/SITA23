/* structure et tableaux de structures */

#include <stdio.h>
#include <stdlib.h>

// on va définir un nouveau type : structure eleve.
typedef struct {
    char nom[20];
    float note;
    } eleve;

 // remplacez les pointillés par les bonnes instructions !!!!!!!!

// fonction qui saisit les champs de l'élève au clavier :
void saisir_eleve(eleve *e)
{
    printf("Donnez le nom de l'élève : \n");
    scanf("%s", e->nom);
    printf("Donnez la note de l'élève : \n");
    scanf("%f", & e->note);
    getchar(); // pour vider le buffer d'entrée
};

// fonction qui affiche les champs de l'élève :
void afficher_eleve(eleve e)
{
    printf("Nom : %s\n", e.nom);
    printf("Note : %f\n", e.note);
};

int main()
{
    eleve moi;
    eleve eux[2];

    saisir_eleve( & moi);
    saisir_eleve( & eux[0]);
    saisir_eleve( eux+1);  // idem que : saisir_eleve(& eux[1]);

    afficher_eleve(moi);
    afficher_eleve(eux[0]);
    afficher_eleve(eux[1]); // idem que : afficher_eleve( *(eux+1) );

    printf("\nPOUR CONTINUER FRAPPER UNE TOUCHE ");
    getchar();
    return 0 ;
}

// ajouter ici les définitions des deux fonctions déclarées ci-dessus.
