
#include <stdio.h>
#include <math.h>
void saisir(int dim, float t[]){
// la fonction "saisir" permet de saisir au clavier "dim" valeurs stockées
// dans le tableau "t".
    int i;
    for (i=0;i<dim; i++){
    scanf("%f", &t[i]);}
}
float moyenne(int dim, float t[]){

// la fonction "moyenne" permet de calculer la moyenne des "dim" valeurs du tableau "t".
    float somme = 0;
    int i;
for (i = 0; i<dim; i++){
    somme += t[i];
    }   
    return somme/dim;
}
float ecart_type(int dim,float t[]){
// la fonction "ecart_type" permet de calculer l'écart-type des "dim" premières valeurs
// du tableau "t".

    float somme_variance = 0;
    int i;
for (i = 0; i<dim; i++){
    somme_variance += pow(t[i],2);
    }
    return sqrt(somme_variance/dim - (pow(moyenne(dim,t),2)));
}

int main()
{
float nombre[10];

saisir(10,nombre);
printf("MOYENNE = %f  ECART_TYPE = %f\n",moyenne(10,nombre),ecart_type(10,nombre));
printf("POUR CONTINUER FRAPPER UNE TOUCHE: ");
getchar();
return 0 ;
}

