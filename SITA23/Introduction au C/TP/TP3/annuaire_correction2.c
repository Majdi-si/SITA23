#include "annuaire.h"

/* ******************************************************************* */
/* fonction affichant les options offertes par le menu � l'utilisateur */
void afficherMenu(){

    printf("\t\t\t\t MENU PRINCIPAL\n\n\n\n");
    printf("\t\t Saisir des personnes          A\n");
    printf("\t\t Supprimer des personnes       S\n");
    printf("\t\t Visualiser l'annuaire         V\n");
    printf("\t\t Quitter                       Q\n\n");
    printf("\t\t Votre choix :");
}

/* ***************************** */
/* fonction du menu principal */
void menu(int *ind,tableau *t){
    char rep;
    do {
        afficherMenu();
        rep=toupper(getchar());
        switch(rep) {
            case 'A' : saisirPersonne(ind,t);break;
            case 'S' : supprimerPersonne(ind,t);break;
            case 'V' : editerAnnuaire(*ind,*t);break;
            case 'Q' : break;
		}
    }while (rep != 'Q');
}

/* ******************************** */
/* fonction de saisie des personnes */
void saisirPersonne(int *index,tableau *t){
    char nomtmp[20];
    int sortie,i;

    printf("\tPour revenir au menu, tapez entree \n");

    do{
        getchar();
        sortie=0;
        /* Le premier emplacement de libre dans le tableau est � l'indice index */
        i=*index;
        if (i==NB_MAX)
        {
            printf("\ntableau complet...\nnouvelle saisie impossible\n");
            getchar();
        }
        else
        {
            printf("\tNOM :");
            strcpy(nomtmp,"");
            scanf("%19[^\n]",nomtmp);
            if (nomtmp[0] != '\0') // le nom n'est pas vide
            {
                sortie=1;
				*t=(personne*)realloc(*t,sizeof(personne)*( *index + 1));
                strcpy((*t)[i].nom,nomtmp);
                printf("\tPRENOM :");
                getchar();
                scanf("%19[^\n]",(*t)[i].prenom);
                printf("\ttel :");
                getchar();
                scanf("%11[^\n]",(*t)[i].tel);
                (*index) ++;
            }
        }
    }while(sortie);
    getchar();
}

/* *************************************** */
/* fonction de suppression des personnes   */
void supprimerPersonne(int *index, tableau * t) {
    char nomtmp[20];
    int i;
    int sortie=0;

    getchar();
    printf("quelle personne voulez-vous supprimer :");
    scanf("%19[^\n]",nomtmp);
    strcpy(nomtmp,nomtmp);
    i=0;
    while(i< *index && !sortie)  // on recherche le nom
	{
        if (!(strcmp((*t)[i].nom,nomtmp))) // le nom est trouv�
	    {

			//on remplace la personne supprimee par le dernier
            (*t)[i] = (*t)[*index-1];
            (*index) --;  // on d�cr�mente le nombre de personnes
            // on r�duit le tableau
			*t=realloc(*t, sizeof(personne) * (*index) );
            sortie=1;
	    }
        else i++;
    }
    if ( !sortie)
        printf("\n personne non trouv�e !!!!!!!\n");
    else
        printf("\n La personne %s a �t� supprim�e !\n",nomtmp);
    getchar();

}

/* ***************************************** */
/*fonction d'�dition de toutes les personnes */
void editerAnnuaire(int index,tableau t){
    int i=0;
    if(index == 0)
        printf("annuaire vide !\n");
    while(i<index)
	{
        printf("\nnom :%s \nprenom :%s \ntel :%s \n\n",t[i].nom,t[i].prenom,t[i].tel);
        i++;
	}
    getchar();
}

/* ************************************************ */
/* */
void chargerFichierTexte(int *index,tableau *t,char* nomfichier)
{
	FILE *fic;
	int i;
	char tampon[30];

	if((fic=fopen(nomfichier,"r"))==NULL)
    {
		printf("Ouverture du fichier impossible");
		getchar();
	}
	else // ouverture du fichier ok
	{
		i=0;
		while ( fgets(tampon,20,fic) != NULL)
		{
			*t=(personne*)realloc(*t, sizeof(personne) * ( i + 1));
			sscanf(tampon,"%19[^\n]",(*t)[i].nom);
            fgets(tampon,20,fic);
            sscanf(tampon,"%19[^\n]",(*t)[i].prenom);
            fgets(tampon,12,fic);
            sscanf(tampon,"%11[^\n]",(*t)[i].tel);
			i++;
		}
        *index=i;
        fclose(fic);
	}
}

/* ******************************************************* */
/* fonction sauvegardant les donn�es dans un fichier texte */
void sauverFichierTexte(int index,tableau *t,char* nomfichier)
{
	FILE *fic;
	int i;

	if((fic=fopen(nomfichier,"w"))==NULL)
	{
		printf("Ouverture Impossible");
		getchar();
	}
	else
	{
		i=0;
		while (i< index)
		{
            fprintf(fic,"%s\n",(*t)[i].nom);
			fprintf(fic,"%s\n",(*t)[i].prenom);
            fprintf(fic,"%s\n",(*t)[i].tel);
            i++;
		}
		fclose(fic);
		// lib�ration m�moire de tout le tableau
		free(*t);
		*t=NULL;
	}

}
