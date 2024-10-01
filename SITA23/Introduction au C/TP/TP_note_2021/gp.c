#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gp.h"
#include <errno.h>

void chargerPilotes(int * nbp, Pilote **pilotes,char * nomfichier){
    FILE *fic=fopen(nomfichier,"r");
    if (fic) {
        int i=0;
        char chaine[100];
        // lecture ligne par ligne dans le fichier
        while (fgets(chaine,100,fic)!=NULL)
            {
             // allocation des structures une par une :
                *pilotes=realloc(*pilotes,sizeof(Pilote)*(i+1));
                //transfert des informations de la ligne dans chacun des champs de la structure :
                sscanf(chaine,"%s %s %d", (*pilotes)[i].nom, (*pilotes)[i].prenom, &(*pilotes)[i].numero);
                (*pilotes)[i].nbPoints=0;
                i++;
            }
        *nbp=i;
    }
    else{
        fprintf(stderr,"pb charger ouverture fichier %s\n", nomfichier);
    }
}

void afficherPilotes(int nbp,Pilote *pilotes){
    for (int i = 0; i<nbp; i++){
        printf("Nom : %s\n", pilotes[i].nom);
        printf("Prénom : %s\n", pilotes[i].prenom);
        printf("Numero : %d \n", pilotes[i].numero);
        printf("Nombre de points : %d \n\n", pilotes[i].nbPoints);

   }
}

void chargerCourses(int *nbc,Course **courses,char * nomfichier){
    FILE *fic=fopen(nomfichier,"r");
    if (fic) {
        int i=0;
        char chaine[100];
        // lecture ligne par ligne dans le fichier
        while (fgets(chaine,100,fic)!=NULL)
            {
             // allocation des structures une par une :
                *courses=realloc(*courses,sizeof(Course)*(i+1));
                //transfert des informations de la ligne dans chacun des champs de la structure :
                sscanf(chaine,"%s %d %d %d %d %d %d %d %d %d %d", (*courses)[i].nom, &(*courses)[i].listePilotes[0],
                 &(*courses)[i].listePilotes[1],&(*courses)[i].listePilotes[2],&(*courses)[i].listePilotes[3],
                 &(*courses)[i].listePilotes[4],&(*courses)[i].listePilotes[5],&(*courses)[i].listePilotes[6],
                 &(*courses)[i].listePilotes[7],&(*courses)[i].listePilotes[8],&(*courses)[i].listePilotes[9]);
                i++;
            }
        *nbc=i;
    }
    else{
        fprintf(stderr,"pb charger ouverture fichier %s\n", nomfichier);
    }
}

void afficherCourses(int nbc,Course *courses){
    for (int i = 0; i<nbc; i++){
        printf("Nom : %s\n", courses[i].nom);
        printf("Listes des pilotes : %d %d %d %d %d %d %d %d %d %d\n\n", courses[i].listePilotes[0],
                 courses[i].listePilotes[1],courses[i].listePilotes[2],courses[i].listePilotes[3],
                 courses[i].listePilotes[4],courses[i].listePilotes[5],courses[i].listePilotes[6],
                 courses[i].listePilotes[7],courses[i].listePilotes[8],courses[i].listePilotes[9]);

   } 
}

void initPointsClassement(int **tabclas){
    int t[]={26,18,15,12,10,8,6,4,2,1};
    *tabclas = (int*)malloc(10*sizeof(int));
    for (int i=0;i<10;i++){
        (*tabclas)[i]=t[i];
    }
}

void calculerPointsPilotes(int nbp,Pilote *pilotes,int *tabclas,int nbc,Course *courses){
    int num_pilote = 0;
    for(int i = 0; i<nbc; i++){
        for(int j = 0; j<10; j++){
            num_pilote = courses[i].listePilotes[j];
            for (int k = 0; k<nbp; k++){
                if ((pilotes)[k].numero == num_pilote){
                    pilotes[k].nbPoints += tabclas[j];
                }
            }
        }
    }
}

void sauverPilotes(int nbp,Pilote *pilotes,char * nomfichier){
    errno = 0;
    FILE *fic = NULL;
    fic = fopen(nomfichier, "w");
    if (errno != 0) {
        printf("Erreur d'ouverture du fichier %s: %s\n", nomfichier, strerror(errno));
        return;
    } 
    else {
        for (int i = 0; i < nbp; i++) {
            if (fputs((pilotes)[i].nom, fic) != EOF) {
                fputc(' ', fic); // Ajouter un espace après l'indicatif
                if (fputs((pilotes)[i].prenom, fic) != EOF) {
                    fputc(' ', fic); // Ajouter un espace après la marque
                    if (fprintf(fic, "%d %d", (pilotes)[i].numero, (pilotes)[i].nbPoints) != EOF) {
                        fputc('\n', fic); // Ajouter un retour à la ligne après le téléphone
                        printf("Transfert réussi \n");
                    }
                }
            }
        }
    }
    fclose(fic); // N'oubliez pas de fermer le fichier
}

void liberer(int *nbp,Pilote **pilotes,int *nbc,Course **courses,int **tabclas){
    if (*pilotes != NULL)
    {
        free(*pilotes);
        *pilotes = NULL;
        *nbp = 0;
    }
    if (*courses != NULL)
    {
        free(*courses);
        *courses = NULL;
        *nbc = 0;
    }
    if (*tabclas != NULL)
    {
        free(*tabclas);
        *tabclas = NULL;
        *nbc = 0;
    }


}