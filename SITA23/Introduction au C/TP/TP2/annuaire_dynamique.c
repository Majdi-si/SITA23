#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NB_MAX 100

typedef struct {
	char nom[20];
	char prenom[20];
	char tel[12];
	} personne;

/* fonction affichant les options offertes par le menu � l'utilisateur */
void afficherMenu();

char* majuscule(char *chaine);

void saisirPersonne(int *index, personne tab[]) {
    if (*index >= NB_MAX) {
        printf("Annuaire plein.\n");
        return;
    }

    printf("Nom : ");
    fgets(tab[*index].nom, 20, stdin);
    majuscule(tab[*index].nom);

    printf("Prenom : ");
    fgets(tab[*index].prenom, 20, stdin);
    majuscule(tab[*index].prenom);

    printf("Telephone : ");
    fgets(tab[*index].tel, 12, stdin);
    
    (*index)++;

    for (int i = 0; i < *index - 1; i++) {
        for (int j = i + 1; j < *index; j++) {
            if (strcmp(tab[i].nom, tab[j].nom) > 0) {
                personne temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}

void supprimerPersonne(int *index, personne tab[]) {
    char nom[20];
    printf("Nom de la personne à supprimer : ");
    fgets(nom, 20, stdin);
    majuscule(nom);

    for (int i = 0; i < *index; i++) {
        if (strcmp(tab[i].nom, nom) == 0) {
            tab[i] = tab[*index - 1]; // Écrase la personne trouvée par la dernière du tableau
            (*index)--; // Décrémente le nombre de personnes du tableau
            printf("Personne supprimée.\n");
            for (int i = 0; i < *index - 1; i++) {
                for (int j = i + 1; j < *index; j++) {
                    if (strcmp(tab[i].nom, tab[j].nom) > 0) {
                        personne temp = tab[i];
                        tab[i] = tab[j];
                        tab[j] = temp;
            }
        }
    }
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

char* majuscule(char *chaine){
    int i = 0;
    int length = strlen(chaine);
    for(i = 0; i<length; i++){
        chaine[i] = toupper(chaine[i]);
    }
    return chaine;
};

int main()
{
    personne*  tab=NULL;  // tableau dynamiques
    int index=0; // nombre de personnes r�elles dans le tableau

    char rep;
    do {
        afficherMenu();
        rep=toupper(getchar());
        getchar();   //pour lire le caractere de passage � la ligne
        switch(rep) {
            case 'A' : saisirPersonne(&index,&tab);break; //passage par adresse car modification de index ds la fonction et allocation de chaque nouvelle structure personne
            case 'S' : supprimerPersonne(&index,&tab);break;  // r�duction du tableau par r�duction m�moire de la structure personne concern�e
            case 'V' : editerAnnuaire(index,tab);break;
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


