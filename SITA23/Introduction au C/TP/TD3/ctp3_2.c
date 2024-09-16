

#include <stdio.h>
#define N 2
#define determ(a,b,c,d) (((a)*(d))-((c)*(b)))

int main()
{
int mat[N][N],det,i,j;
/* saisie */
printf("ENTRER SUCCESSIVEMENT LES VALEURS DEMANDEES: \n");
/* ajouter les instructions pour saisir au clavier chaque valeur de la matrice 2x2 mat : */

for (i=0; i<N; i++){
    for (j=0; j<N; j++){
        scanf("%d", &mat[i][j]);
    }
}


/* ajouter les instructions du calcul du déterminant :
det=(mat[0][0] x mat[1][1]) - (mat[1][0] x mat[0][1])*/
/* on pourra utiliser la macro determ définie ci-dessus */

det = determ(mat[0][0],mat[1][1],mat[1][0],mat[0][1]);

/* ajouter les instructions d'affichage de la matrice :*/

for (i=0; i<N; i++){
    for (j=0; j<N; j++){
        printf("La valeur en (%d, %d) vaut %d\n", i,j,mat[i][j]);
    }
}

printf("DETERMINANT = %d\n",det);
printf("POUR CONTINUER FRAPPER  UNE TOUCHE: ");
getchar();
return 0 ;
}

