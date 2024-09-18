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
