/* saisie d'une chaîne de caractères de taille non définie */
#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *adr_deb = NULL, c;
  int taille = 1;
  // réservation initiale de la chaîne :
  adr_deb = (char *) calloc(taille, sizeof(char));
  /* chaîne de taille initiale 1 caractère */

  /* saisie et rangement du texte */
  printf("ADRESSE DU TEXTE: %p (ATTRIBUEE A L'EXECUTION)\n", adr_deb);
  printf("ENTRER UN TEXTE ('\\n' pour terminer): ");

  while ( (c = getchar()) != '\n' )
    {
      // on alloue une case en plus :
      taille++;
      adr_deb = realloc(adr_deb, taille);
      // on déplace le caractère de fin de chaîne :
      *(adr_deb + taille - 1) = *(adr_deb + taille - 2);
      // on stocke le caractère tapé :
      *(adr_deb + taille - 2) = c;
    }

  /* resultats */
  printf("CHAINE SAISIE : %s\n", adr_deb);
  printf("TAILLE : %d\n", taille);
  free(adr_deb); // libération mémoire de la zone réservée
  adr_deb = NULL;

  return 0 ;
}
