#include <stdio.h>
#include <string.h>
#include "mesfonctions.h"

int main()
{
    Genome *variole=NULL; // pointeur sur une structure Genome

    // chargement à partir du fichier "variole.txt" :
    chargerGenome(&variole, "variole.txt");

    // affichage du génome à l'écran :
    afficherGenome( *variole);

    printf("\nnucléotide A=%d ",calculerNbreNucleotide(*variole, 'A'));
	printf("\nnucléotide C=%d ",calculerNbreNucleotide(*variole, 'C'));
	printf("\nnucléotide G=%d ",calculerNbreNucleotide(*variole, 'G'));
	printf("\nnucléotide T=%d ",calculerNbreNucleotide(*variole, 'T'));

	printf("ma= %lf\n", calculerMasseAtomiqueTotale( *variole ));

	// ajout d'un gène à la position 10 :
	ajouterGene(&variole,"CACACACACACA",10);

	// sauvegarde du génome dans un fichier texte :
    sauverGenome("varioleOGM.txt", *variole);
    libererGenome(&variole);

	return 0;
}
