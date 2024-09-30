#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mesfonctions.h"

// masse atomique :
#define MA_A 135.1267
#define MA_G 151.1261
#define MA_T 126.1133
#define MA_C 111.102

/********************************************/
/* affiche � l'�cran l'ensemble des caract�ristiques du g�nome */
void afficherGenome(Genome g)
{
    int i;
	int nbre=60;
	// parcours de l'ensemble des caract�res du champ data :
    for (i=0;g.data[i] != '\0' ;i++)
    {
        printf("%c", g.data[i]);
        if (i%nbre ==0) {
		    printf("\n");
        }
	}
}

/**************************************************/
/*   r�cup�re du fichier l'ensemble du g�nome pour r�server et remplir la structure */
// version 1 : lecture du fichier par paquet de 999 caract�res
/*
void chargerGenome(Genome **g, char * nomfichier)
{
    FILE *fic=fopen(nomfichier,"r");
    if (fic)
    {
        char chaine[1000]="";
        *g=malloc(sizeof(Genome)); // allocation m�moire de la structure
        (*g)->data[0]='\0'; // initialisation � la cha�ne vide
        while (fgets(chaine,999,fic) != NULL) // parcours du fichier par tranche de 999 caract�res
        {
            // on supprime le '\n' � la fin de la chaine s'il y en a un:
            char *p=strchr(chaine,'\n');
            if (p)
                *p='\0';
            // on concat�ne la chaine � la fin des donn�es du champ data de la structure :
            strcat((*g)->data,chaine);
        }
        fclose(fic);
        // on met � jour les autres champs :
        (*g)->nbA=calculerNbreNucleotide(**g,'A');
        (*g)->nbC=calculerNbreNucleotide(**g,'C');
        (*g)->nbG=calculerNbreNucleotide(**g,'G');
        (*g)->nbT=calculerNbreNucleotide(**g,'T');
    }
    else
        fprintf(stderr,"pb charger ouverture fichier %s\n", nomfichier);
}
*/

/**************************************************/
/*   r�cup�re du fichier l'ensemble du g�nome pour r�server et remplir la structure */
// version 2 : lecture en une seule �tape du fichier
void chargerGenome(Genome **g, char * nomfichier)
{
    FILE *fic=fopen(nomfichier,"r");
    if (fic)
    {
        *g=malloc(sizeof(Genome)); // allocation m�moire de la structure
        (*g)->data[0]='\0'; // initialisation � la cha�ne vide
        fgets( (*g)->data,NBMAX,fic);
        // on supprime le '\n' � la fin de la chaine s'il y en a un:
        char *p=strchr( (*g)->data,'\n');
        if (p)
            *p='\0';
        fclose(fic);
        // on met � jour les autres champs :
        (*g)->nbA=calculerNbreNucleotide(**g,'A');
        (*g)->nbC=calculerNbreNucleotide(**g,'C');
        (*g)->nbG=calculerNbreNucleotide(**g,'G');
        (*g)->nbT=calculerNbreNucleotide(**g,'T');
    }
    else
        fprintf(stderr,"pb charger ouverture fichier %s\n", nomfichier);
}

/**************************************************/
// calcul de la masse atomique de l'ensemble du g�nome
double calculerMasseAtomiqueTotale(Genome g)
{
    double d=g.nbA * MA_A + g.nbC * MA_C + g.nbT * MA_T + g.nbG * MA_G ;
    return d;
}

/***********************************************/
// calcul du nombre de nucl�otide de type n dans le champ data de g
int calculerNbreNucleotide(Genome g, char n)
{
    int somme=0,i;
    for (i=0;g.data[i] != '\0' ; i++ )
    {
        if (g.data[i] == n)
            somme++;
    }
     return somme;
}

/*******************************************************/
// insertion d'un g�ne � la position "position" dans le champ data
void ajouterGene(Genome **g, char *gene, int position)
{
    char chaine [NBMAX]=""; // cha�ne resultat final
    int lng=strlen((*g)->data); // longueur du g�nome initial
    if ( lng + strlen(gene) < NBMAX-1) // si la taille du g�nome est inf�rieure � la taille max
    {
        // on r�cup�re les premieres lettres jusqu'� position :
        strncpy(chaine,(*g)->data ,position);
        // on ajoute le nouveau g�ne :
        strcat(chaine,gene);
        // on concat�ne la suite du g�nome initial
        strcat(chaine, (*g)->data + position);
        // on remplace le g�nome par le nouveau :
        strcpy( (*g)->data,chaine);
         // on met � jour les autres champs :
        (*g)->nbA=calculerNbreNucleotide(**g,'A');
        (*g)->nbC=calculerNbreNucleotide(**g,'C');
        (*g)->nbG=calculerNbreNucleotide(**g,'G');
        (*g)->nbT=calculerNbreNucleotide(**g,'T');
    }
    else
        printf("ajout impossible champ data taille insuffisante!!!");
}

/********************************************************/
// sauvegarde dans un fichier :

/* version 1 : caract�re par caract�re :
void sauverGenome(char *nomfichier, Genome g)
{
    FILE *fic=fopen(nomfichier,"w");
    if (fic)
    {
        int i;
        for (i=0;g.data[i] != '\0' ;i++)
        {
           // �criture caract�re par caract�re dans le fichier :
           fputc(g.data[i],fic);
        }
        fclose(fic);
    }
    else
        fprintf(stderr,"pb sauver ouverture fichier %s\n", nomfichier);
}
*/

/********************************************************/
// sauvegarde dans un fichier :

/* version 2 : toute la cha�ne en une seule fois : */
void sauverGenome(char *nomfichier, Genome g)
{
    FILE *fic=fopen(nomfichier,"w");
    if (fic)
    {
        fputs(g.data,fic);
        fclose(fic);
    }
    else
        fprintf(stderr,"pb sauver ouverture fichier %s\n", nomfichier);
}

/********************************************************/
// sauvegarde dans un fichier :
/* version 3 : �criture par paquet de 1000 caract�res dans le fichier */
/*
void sauverGenome(char *nomfichier, Genome g)
{
    FILE *fic=fopen(nomfichier,"w");
    if (fic)
    {
        int i;
        const int LNMAX=1000;
        char chaine[LNMAX + 1];
        int lng=strlen( g.data);
        for (i=0;i< lng ;i +=LNMAX)
        {
           strncpy(chaine,g.data+i, LNMAX);
           chaine[LNMAX]='\0';
           fprintf(fic,"%s",chaine);
        }
        fclose(fic);
    }
    else
        fprintf(stderr,"pb sauver ouverture fichier %s\n", nomfichier);
}
*/
/********************************************************/
// lib�ration m�moire de la structure :
void libererGenome(Genome **g)
{
    if (*g)
	{
		free(*g);
		*g=NULL;
	}
}
