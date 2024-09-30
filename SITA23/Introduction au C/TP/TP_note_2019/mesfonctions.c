#include "mesfonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


void enlever_retour_chariot(char *chaine){
    int i = 0;
    while(chaine[i] != '\0'){
        if(chaine[i] == '\n'){
            chaine[i] = '\0';
        }
        i++;
    }
}


/************************************/
/*  saisie clavier des caract�ristiques d'un avion � la fin du tableau statique */
void saisir( int *nb, Avion *t)
{
    if (*nb >= NBMAX) {
        printf("Nb avions plein.\n");
        return;
    }

    printf("Indicatif : ");
    fgets((t)[*nb].indicatif, 20, stdin);
    enlever_retour_chariot((t)[*nb].indicatif);


    printf("Marque : ");
    fgets((t)[*nb].marque, 20, stdin);
    enlever_retour_chariot((t)[*nb].marque);

    printf("Type : ");
    fgets((t)[*nb].type, 20, stdin);
    enlever_retour_chariot((t)[*nb].type);

    printf("Nombre de places : ");
    scanf("%d", &(t)[*nb].nbplaces);

    printf("Nombre de réservations : ");
    scanf("%d", &(t)[*nb].nbresa);
    
    (*nb)++;
    getchar();
}

/*******************************/
/*  saisie clavier des caract�ristiques d'un avion : ajout dans le tableau dynamique
    par agrandissement */
void saisirDyn( int *nb, Avion **t)
{
    *t = (Avion *)realloc(*t, (*nb + 1) * sizeof(Avion));
    if (*nb >= NBMAX) {
        printf("Nb avions plein.\n");
        return;
    }

    printf("Indicatif : ");
    fgets((*t)[*nb].indicatif, 20, stdin);
    enlever_retour_chariot((*t)[*nb].indicatif);


    printf("Marque : ");
    fgets((*t)[*nb].marque, 20, stdin);
    enlever_retour_chariot((*t)[*nb].marque);

    printf("Type : ");
    fgets((*t)[*nb].type, 20, stdin);
    enlever_retour_chariot((*t)[*nb].type);

    printf("Nombre de places : ");
    scanf("%d", &(*t)[*nb].nbplaces);

    printf("Nombre de réservations : ");
    scanf("%d", &(*t)[*nb].nbresa);
    
    (*nb)++;
    getchar();
 }
/*********************************/
/*  affiche pour chaque avion du tableau son taux d'occupation, cad rapport de nombre de resa sur
le nombre de places */
void calculerOccupation(int nb,Avion *t)
{
    for (int i = 0; i<nb; i++){
        printf("%s a un taux d'occupation de : %.2f %",t[i].indicatif, (t[i].nbresa*100.0) / t[i].nbplaces );
    }
}

/******************************************/
/* chargement dans le tableau statique des avions � partir du fichier texte  */
void charger(int *n, Avion *t, char *nomfichier){

  // version 2 : lecture en une seule �tape du fichier

    FILE *fic=fopen(nomfichier,"r");
    if (fic)
    {
        (t)->indicatif[0]='\0'; // initialisation � la cha�ne vide
        t->marque[0]='\0';
        t->type[0]='\0';
        t->nbplaces=0;
        t->nbresa=0;
        int i=0;
        while (fscanf(fic,"%s %s %s %d %d", t[i].indicatif,t[i].marque,t[i].type, &t[i].nbplaces, &t[i].nbresa) == 5 && i<NBMAX)
        {
            i++;
        }
        *n=i;
    }
    else{
        fprintf(stderr,"pb charger ouverture fichier %s\n", nomfichier);
}
}

/**********************************/
/* affichage des caract�ristiques de chaque avion du tableau � l'�cran */
void afficher(int nb, Avion *t)
{
   for (int i = 0; i<nb; i++){
    printf("Indicatif : %s\n", t[i].indicatif);
    printf("Marque : %s\n", t[i].marque);
    printf("Type : %s\n", t[i].type);
    printf("Nombre de places : %d \n", t[i].nbplaces);
    printf("Nombre de réservations : %d \n", t[i].nbresa);

   }
}

/**********************************/
/*  sauvegarde dans un fichier texte des caract�ristiques de chaque avion (une ligne par avion) */
void sauver(int nb, Avion *t,char * nomfichier)
{
    errno = 0;
    FILE *fic = NULL;
    fic = fopen(nomfichier, "w");
    if (errno != 0) {
        printf("Erreur d'ouverture du fichier %s: %s\n", nomfichier, strerror(errno));
        return;
    } 
    else {
        for (int i = 0; i < nb; i++) {
            if (fputs((t)[i].indicatif, fic) != EOF) {
                fputc(' ', fic); // Ajouter un espace après l'indicatif
                if (fputs((t)[i].marque, fic) != EOF) {
                    fputc(' ', fic); // Ajouter un espace après la marque
                    if (fputs((t)[i].type, fic) != EOF) {
                        fputc(' ', fic); // Ajouter un espace après la marque
                        if (fprintf(fic, "%d %d", (t)[i].nbplaces, (t)[i].nbresa) != EOF) {
                            fputc('\n', fic); // Ajouter un retour à la ligne après le téléphone
                            printf("Transfert réussi \n");
                        }   
                    }
                }
            }
        }
    }
    fclose(fic); // N'oubliez pas de fermer le fichier
}

/**********************************/
/* lib�ration m�moire du tableau dynamique */
void liberer(int *nb, Avion **t)
{
    if (*t != NULL)
    {
        free(*t);
        *t = NULL;
        *nb = 0;
    }
}
