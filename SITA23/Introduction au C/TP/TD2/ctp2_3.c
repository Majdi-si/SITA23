/************ calcul de la factorielle ***********/
#include <stdio.h>
int main()
{
    int n,i,fac= 1;
    printf("ENTRER UN ENTIER: ");
    scanf("%d",&n);

    for (i = 1; i<=n; i++){
        fac *= i;
    }

    printf("\nn = %d  n! = %d\n",n,fac);

    return 0 ;
}


