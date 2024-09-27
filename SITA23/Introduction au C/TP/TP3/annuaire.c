#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "annuaire.h" 
#include <errno.h>

#define NB_MAX 100



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

void enlever_retour_chariot(char *chaine){
    int i = 0;
    while(chaine[i] != '\0'){
        if(chaine[i] == '\n'){
            chaine[i] = '\0';
        }
        i++;
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

void saisirPersonne(int *index, personne **tab) {
    *tab = (personne*)realloc(*tab, (*index + 1) * sizeof(personne));
    if (*index >= NB_MAX) {
        printf("Annuaire plein.\n");
        return;
    }

    printf("Nom : ");
    fgets((*tab)[*index].nom, 20, stdin);
    enlever_retour_chariot((*tab)[*index].nom);
    majuscule((*tab)[*index].nom);

    printf("Prenom : ");
    fgets((*tab)[*index].prenom, 20, stdin);
    enlever_retour_chariot((*tab)[*index].prenom);
    majuscule((*tab)[*index].prenom);

    printf("Telephone : ");
    fgets((*tab)[*index].tel, 12, stdin);
    enlever_retour_chariot((*tab)[*index].tel);
    
    (*index)++;

    for (int i = 0; i < *index - 1; i++) {
        for (int j = i + 1; j < *index; j++) {
            if (strcmp((*tab)[i].nom, (*tab)[j].nom) > 0) {
                personne temp = (*tab)[i];
                (*tab)[i] = (*tab)[j];
                (*tab)[j] = temp;
            }
        }
    }
}

void supprimerPersonne(int *index, personne **tab) {
    char nom[20];
    printf("Nom de la personne à supprimer : ");
    fgets(nom, 20, stdin);
    majuscule(nom);

    for (int i = 0; i < *index; i++) {
        if (strcmp((*tab)[i].nom, nom) == 0) {
            (*tab)[i] = (*tab)[*index - 1]; // Écrase la personne trouvée par la dernière du tableau
            (*index)--; // Décrémente le nombre de personnes du tableau
            *tab = realloc(*tab, (*index) * sizeof(personne)); // Réduire la taille du tableau
            if (*tab == NULL && *index > 0) {
                printf("Erreur de réallocation mémoire.\n");
                exit(1);
            }
            printf("Personne supprimée.\n");
            return;
        }
    }
    printf("Personne non trouvée.\n");
};

void editerAnnuaire(int *index, personne **tab){
    if (*index == 0) {
        printf("Annuaire vide.\n");
        return;
    }

    for (int i = 0; i < *index; i++) {
        printf("Nom : %s\n", (*tab)[i].nom);
        printf("Prenom : %s\n", (*tab)[i].prenom);
        printf("Telephone : %s\n", (*tab)[i].tel);
        printf("\n");
    }
}

void ecrire_fichier(char *nomfic, personne **tab, int *index) {
    errno = 0;
    FILE *fic = NULL;
    fic = fopen(nomfic, "a");
    if (errno != 0) {
        printf("Erreur d'ouverture du fichier %s: %s\n", nomfic, strerror(errno));
        return;
    } else {
        for (int i = 0; i < *index; i++) {
            if (fputs((*tab)[i].nom, fic) != EOF) {
                fputc(' ', fic); // Ajouter un espace après le nom
                if (fputs((*tab)[i].prenom, fic) != EOF) {
                    fputc(' ', fic); // Ajouter un espace après le prénom
                    if (fputs((*tab)[i].tel, fic) != EOF) {
                        fputc('\n', fic); // Ajouter un retour à la ligne après le téléphone
                        printf("Transfert réussi \n");
                    }
                }
            }
        }
    }
    fclose(fic); // N'oubliez pas de fermer le fichier
}

personne* chargerFichierTexte(char *nomfic, int *index) {
    errno = 0;
    FILE *fic = NULL;
    personne *tab = NULL;
    *index = 0;

    fic = fopen(nomfic, "r");
    if (errno != 0) {
        printf("Erreur d'ouverture du fichier %s: %s\n", nomfic, strerror(errno));
        return NULL;
    } else {
        while (!feof(fic)) {
            tab = (personne*)realloc(tab, (*index + 1) * sizeof(personne));
            if (*index >= NB_MAX) {
                printf("Annuaire plein.\n");
                fclose(fic);
                return tab;
            }
            if (fscanf(fic, "%s %s %s", tab[*index].nom, tab[*index].prenom, tab[*index].tel) == 3) {
                (*index)++;
            }
        }
    }
    fclose(fic);
    return tab;
}
