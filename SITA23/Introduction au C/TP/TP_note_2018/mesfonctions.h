#ifndef MESFONCTIONS_H_INCLUDED
#define MESFONCTIONS_H_INCLUDED

// longueur max du genome :
#define NBMAX 200000

typedef struct {
    char data[NBMAX]; // liste des caract�res du g�nome
 	int nbA; // nombre de nucl�otide A dans le g�nome
	int nbC; // nombre de nucl�otide C dans le g�nome
	int nbG; // nombre de nucl�otide G dans le g�nome
	int nbT; // nombre de nucl�otide T dans le g�nome
} Genome;

void afficherGenome(Genome g);
void chargerGenome(Genome **g, char * nomfichier);
double calculerMasseAtomiqueTotale(Genome g);
int calculerNbreNucleotide(Genome g, char n);
void ajouterGene(Genome **g, char *gene, int position);
void sauverGenome(char *ch, Genome g);
void libererGenome(Genome **g);

#endif // MESFONCTIONS_H_INCLUDED
