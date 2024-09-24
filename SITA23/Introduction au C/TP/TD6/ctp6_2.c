#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "ctp6_2.h"
#include <string.h>

/* fonction affichant le contenu d'un fichier texte � l'�cran */
void afficher_fichier(char * nomfic)
{
    errno = 0;
    FILE * fic = NULL;
    fic = fopen(nomfic, "r");
    if (errno != 0)
    {
        printf("Erreur d'ouverture du fichier %s: %s\n", nomfic, strerror(errno));
        return;
    }
    else
    {
        char c;
        while ((c=fgetc(fic))!=EOF)
        {
            printf("%c",c);
        }
        fclose(fic);
    }
}

/* fonction �crivant dans un fichier texte le contenu du deuxi�me param�tre : */
void ecrire_fichier(char * nomfic, char * texte){
    errno = 0;
    FILE * fic = NULL;
    fic = fopen(nomfic,"w");
    if (errno != 0)
    {
        printf("Erreur d'ouverture du fichier %s: %s\n", nomfic, strerror(errno));
        return;
    }
    else{
        if (fputs(texte,fic) != EOF){
            printf("Transfert réussi \n");
        }
    }
    fclose(fic);
}

/****************************/
/* fonction qui saisit au clavier une cha�ne de longueur quelconque,
    ==> r�servation dynamique de la cha�ne
*/
int saisir_chaine(char * *ch)
{
    char c;
    int taille = 1;
    // réservation initiale de la chaîne :
    *ch= (char *) calloc(taille, sizeof(char));
    /* chaîne de taille initiale 1 caractère */
    
    while ( (c = getchar()) != '\n' )
        {
        // on alloue une case en plus :
        taille++;
        *ch = realloc(*ch, taille);
        // on déplace le caractère de fin de chaîne :
        *(*ch + taille - 1) = *(*ch + taille - 2);
        // on stocke le caractère tapé :
        *(*ch + taille - 2) = c;
        }
    return taille;



}
