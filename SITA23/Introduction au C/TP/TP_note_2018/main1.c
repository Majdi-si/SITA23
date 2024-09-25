#include <stdio.h>
#include <string.h>
#include "mesfonctions.h"

int main()
{
    Genome *variole=NULL; // pointeur sur une structure Genome

    // chargement � partir du fichier "variole.txt" :
    chargerGenome(&variole, "variole.txt");

    // affichage du g�nome � l'�cran :
    afficherGenome( *variole);

    printf("\nnucl�otide A=%d ",calculerNbreNucleotide(*variole, 'A'));
	printf("\nnucl�otide C=%d ",calculerNbreNucleotide(*variole, 'C'));
	printf("\nnucl�otide G=%d ",calculerNbreNucleotide(*variole, 'G'));
	printf("\nnucl�otide T=%d ",calculerNbreNucleotide(*variole, 'T'));

	printf("ma= %lf\n", calculerMasseAtomiqueTotale( *variole ));

	// ajout d'un g�ne � la position 10 :
	ajouterGene(&variole,"CACACACACACA",10);

	// sauvegarde du g�nome dans un fichier texte :
    sauverGenome("varioleOGM.txt", *variole);
    libererGenome(&variole);

	return 0;
}
