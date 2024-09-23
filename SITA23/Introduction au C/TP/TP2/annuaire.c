#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> 

#define NB_MAX 500

typedef struct {
	char nom[20];
	char prenom[20];
	char tel[12];
	} personne;
	
/* fonction affichant les options offertes par le menu � l'utilisateur */
void afficherMenu();

void saisirPersonne(int *index, personne tab[]) {
    if (*index >= NB_MAX) {
        printf("Annuaire plein.\n");
        return;
    }

    printf("Nom : ");
    fgets(tab[*index].nom, 20, stdin);

    printf("Prenom : ");
    fgets(tab[*index].prenom, 20, stdin);

    printf("Telephone : ");
    fgets(tab[*index].tel, 12, stdin);

    (*index)++;
}

void supprimerPersonne(int *index, personne tab[]) {
    char nom[20];
    printf("Nom de la personne à supprimer : ");
    fgets(nom, 20, stdin);
    printf("Nom saisi : %s\n", nom);

    for (int i = 0; i < *index; i++) {
        printf("Nom dans le tableau : %s\n", tab[i].nom);
        if (strcmp(tab[i].nom, nom) == 0) {
            tab[i] = tab[*index - 1]; // Écrase la personne trouvée par la dernière du tableau
            (*index)--; // Décrémente le nombre de personnes du tableau
            printf("Personne supprimée.\n");
            return;
        }
    }
    printf("Personne non trouvée.\n");
}

void editerAnnuaire(int *index, personne tab[]){
    if (*index == 0) {
        printf("Annuaire vide.\n");
        return;
    }

    for (int i = 0; i < *index; i++) {
        printf("Nom : %s\n", tab[i].nom);
        printf("Prenom : %s\n", tab[i].prenom);
        printf("Telephone : %s\n", tab[i].tel);
        printf("\n");
    }
}

char 

int main()
{
    personne tab[NB_MAX];  // tableau contenant toutes les personnes
    int index=0; // nombre de personnes r�elles dans le tableau
    
    char rep;
    do {
        afficherMenu();
        rep=toupper(getchar());
        getchar();   //pour lire le caractere de passage � la ligne
        switch(rep) {
            case 'A' : saisirPersonne(&index,tab);break; //passage par adresse car modification de index ds la fonction
            case 'S' : supprimerPersonne(&index,tab);break;
            case 'V' : editerAnnuaire(&index,tab);break;
            case 'Q' : break;
		}
    }while (rep != 'Q');
    
    return 0;
}

/* ******************************** */
/* fonction affichant les options offertes par le menu � l'utilisateur */
void afficherMenu(){

    printf("\t\t\t\t MENU PRINCIPAL\n\n\n\n");
    printf("\t\t Saisir des personnes          A\n");
    printf("\t\t Supprimer des personnes       S\n");
    printf("\t\t Visualiser l'annuaire         V\n");
    printf("\t\t Quitter                       Q\n\n");
    printf("\t\t Votre choix :");
}


