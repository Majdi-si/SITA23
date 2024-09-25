#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
// #include <mesfonctions.h>
#include <string.h>

int calculNbreNucleotide(Genome g, char n){
    int i = 0;
    int compteur;
    while(g.data[i] != '\0'){
        if(g.data[i] == n){
            compteur++;
        }
        i++;
    }
    return compteur;
}

int main(){
    Genome g;
    strcpy(g.data, "ACGTAAGTC");
    g.nbA = 0;
    g.nbC = 0;
    g.nbG = 0;
    g.nbT = 0;
    printf("Nombre nucléotides : %d",calculerNbreNucleotide(g, 'A'));
}