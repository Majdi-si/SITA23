
#include <stdio.h>
#include <math.h>
/* utilisation du #define pour définir une expression */
#define NB 10

int main(){
    
float nombre[NB],moyenne = 0,ecart_type = 0;
int i = 0 ;

/* saisie des nombres */
printf("SAISIR 10 NOMBRES SEPARES PAR RETURN : \n");
/* ajouter une boucle for qui permet de saisir les 10 nombres
    pour les stocker dans le tableau de valeurs */

float saisie;
float entree;
for (i=0;i<NB; i++){
    scanf("%f", &nombre[i]);
}

/* calculs :
Faire une boucle for qui calcule la moyenne et l'écart type */

float somme = 0;
float somme_variance = 0;
for (i = 0; i<NB; i++){
    somme += nombre[i];
    somme_variance += pow(nombre[i],2);
}
moyenne = somme/NB;
ecart_type = sqrt(somme_variance/NB - (pow(moyenne,2)));


printf("MOYENNE = %f  ECART_TYPE = %f\n",moyenne,ecart_type);
printf("POUR CONTINUER FRAPPER UNE TOUCHE: ");
getchar();
return 0 ;
}
