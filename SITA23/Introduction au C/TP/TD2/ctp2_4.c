/************ calcule si un nombre est premier ***********/
#include <stdio.h>
int main()
{
    int i, resultat=0;
    int res_scan = 1;
    char n;
    int m;
    while (1)
    {
    printf("ENTRER UN ENTIER: ");
    res_scan = scanf("%c",&n);
    if (res_scan == 1){
        if (n == '\n')
        {
			printf("Arret du programme utilisateur\n");
		    break;
        }
		else
			{
			    //printf("On remet %c \n", c);
			    ungetc(n, stdin);

    }
    scanf("%d",&m);
    for (i=2; i<=m; i++){
        if (m%i == 0){
            break;
        }
        else {
            resultat = 1;
        }
    }
        if (resultat == 1)
        printf("Le nombre %d est premier ! \n",m);
    else
        printf("Le nombre %d n'est pas premier ! \n",m);
    }
    do {    n=getchar();
	       } 
	while (n!='\n') ;
    }
    return 0 ;
}


