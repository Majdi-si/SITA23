#include <stdio.h>
#include <string.h>
#include <errno.h>   // gestion des erreurs
int main()
{
    char nomfic[]="fic123456789.txt"; // nom du fichier que l'on va essayer d'ouvrir : il ne doit pas exister.

    /* On réinitialise errno avant d'appeler la fonction susceptible d'engendrer une erreur */
    errno = 0;

    FILE *fic=fopen(nomfic,"r");

     if (errno != 0)
    {
        /* Il y a eu une erreur ! */
        fprintf(stderr, "Impossible d'ouvrir le fichier '%s' : '%s'\n",nomfic, strerror(errno));
        //perror("Impossible d'ouvrir ce fichier");
    }
    else
    {
       printf("ouverture en lecture réussie\n quel coup de bol!\n");
       fclose(fic);
    }
    printf("FIN\n");
    return 0;
}

