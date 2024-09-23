/* saisie d'une chaîne de caractères de taille non définie */
#include <stdio.h>
#include <stdlib.h>

/* fonction qui saisit une chaîne de taille non définie (réservation dynamique) */
/* retourne la taille de la chaîne (nombre de caractères + '\0') */
int saisir_chaine(char **ch);

int main()
{
  char *adr_deb = NULL;
  int taille = 0;

  printf("ENTRER UN TEXTE ('\\n' pour terminer): ");
  taille = saisir_chaine(&adr_deb);

  /* resultats */
  printf("CHAINE SAISIE : %s\n", adr_deb);
  printf("TAILLE : %d\n", taille);

  free(adr_deb); // libération mémoire de la zone réservée
  adr_deb = NULL;

  return 0 ;
}

/********************************/
/* ajouter ici la définition de la fonction "saisir_chaine" :
   Cette fonction saisit une chaîne de caractères au clavier dont la taille
   n'est pas connue à l'avance. L'espace mémoire pour stocker les caractères
   est la mémoire dynamique.
   Cette fonction retourne le nombre de caractères de la chaîne (+ '\0').
*/

int saisir_chaine(char** ch){
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
}  // fin de la fonction saisir_chaine
