#include "annuaire.h"

int main()
{
    tableau tab;  // tableau contenant toutes les personnes
    int index=0; // nombre de personnes réelles dans le tableau
    char nomfic[100]="fichierpersonnes.txt"; // nom du fichier texte contenant les personnes : fichier texte

    chargerFichierTexte(&index,tab,nomfic);
    menu(&index,tab);
    sauverFichierTexte(index,tab,nomfic);
	ConteneurMalloc_Affiche (true); // affiche les fuites mémoires
	getchar();
    return 0;
}
