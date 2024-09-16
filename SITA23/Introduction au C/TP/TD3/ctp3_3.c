#include <ctype.h>
#include <stdio.h>
int voyelle(char c) ;

int  main()
{
char c;

printf("ENTRER UN CARACTERE: ");
scanf("%s", &c);
/*
on appelle ici la fonction "voyellle" :
*/
if (voyelle(c))
    printf("CE CARACTERE EST UNE VOYELLE\n");
else
    printf("CE CARACTERE N'EST PAS UNE VOYELLE\n");

printf("POUR CONTINUER FRAPPER UNE TOUCHE ");
getchar();
return 0 ;
}

int voyelle (char c){
    c = toupper(c);
    switch (c)
    {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'Y':
        return 1;
    
    default:
        return 0;
    }
}