#include <stdio.h>
#include <stdlib.h>

void permuter_pasbon(int a, int b);
void permuter_bon(int *a, int *b);

int main()
{
  int x1, x2;
  printf("TAPER AU CLAVIER UNE VALEUR POUR x1 :");
  scanf("%d", &x1);
  printf("TAPER AU CLAVIER UNE VALEUR POUR x2 :");
  scanf("%d", &x2);

  permuter_pasbon(x1, x2);
  printf("Pas bon : VALEUR POUR x1 = %d   VALEUR POUR x2 = %d \n", x1, x2);

  permuter_bon(&x1, &x2);
  printf("Bon : VALEUR POUR x1 = %d   VALEUR POUR x2 = %d \n", x1, x2);

  return 0 ;
}

// définition de la fonction "permuter_pasbon" :
void permuter_pasbon(int a, int b)
{
  int c = a;
  a = b;
  b = c;
}

/*************************************************/
/* écrire ici la définition de la fonction "permuter_bon"
  qui permet de permuter correctement le contenu des variables 
  passées en paramètres
*/

void permuter_bon(int *a, int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

