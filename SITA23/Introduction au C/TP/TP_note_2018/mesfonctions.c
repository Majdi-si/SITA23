#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "mesfonctions.h"
#include <string.h>


void enlever_retour_chariot(char *chaine){
    int i = 0;
    while(chaine[i] != '\0'){
        if(chaine[i] == '\n'){
            chaine[i] = '\0';
        }
        i++;
    }
}


int calculerNbreNucleotide(Genome g, char n){
    int i = 0;
    int compteur = 0;
    while(g.data[i] != '\0'){
        if(g.data[i] == n){
            compteur++;
        }
        i++;
    }
    return compteur;
}

void chargerGenome(Genome** g, char* nomfichier){
    errno = 0;
    FILE *fic = NULL;

    fic = fopen(nomfichier, "r");
    if (errno != 0) {
        printf("Erreur d'ouverture du fichier %s: %s\n", nomfichier, strerror(errno));
        return ;
    }   
    else {
        while (!feof(fic)) {
                *g = (Genome*)calloc(1, sizeof(Genome));
                if(*g == NULL){
                    printf("Erreur d'allocation mémoire\n");
                    fclose(fic);
                return;
            }
            fgets((*g)->data, NBMAX, fic);
            enlever_retour_chariot((*g)->data);
            (*g)->nbA=calculerNbreNucleotide(**g,'A');
            printf("%d\n", (*g)->nbA);
            (*g)->nbC=calculerNbreNucleotide(**g,'C');
            (*g)->nbG=calculerNbreNucleotide(**g,'G');
            (*g)->nbT=calculerNbreNucleotide(**g,'T');
            
            }
        }
        fclose(fic);
}


void afficherGenome(Genome g){
    int i;
	int nbre=60;
	// parcours de l'ensemble des caract�res du champ data :
    for (i=0;g.data[i] != '\0' ;i++)
    {
        printf("%c", g.data[i]);
        if (i%nbre ==0) {
		    printf("\n");
        }
	}
}

double calculMasseAtomiqueTotale(Genome g){
    double somme = 0;
    double masse_A = 0;
    double masse_C = 0;
    double masse_G = 0;
    double masse_T = 0;

    masse_A = g.nbA*135.1267;
    masse_C = g.nbC*111.102;
    masse_G = g.nbG*151.1261;
    masse_T = g.nbT*126.1133;

    somme = masse_A + masse_C + masse_G + masse_T;

    return somme;
}

void ajouterGene(Genome **g, char* gene, int p){
    char chaine = "";
    
}

int main(){
    Genome *g = NULL;
    chargerGenome(&g, "variole.txt");
    afficherGenome(*g);
    
}