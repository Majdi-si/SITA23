#include <ctype.h>
#include <stdio.h>
    /*
int  main()
{
    char c;
    int test = 1;
    printf("ENTRER UN CARACTERE: ");
    scanf("%s", &c);
    c = toupper(c);
    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c =='U' || c == 'Y'){
        printf("Le caractère %c est une voyelle \n", tolower(c));
    }
    else{
        printf("Le caractère %c n'est pas une voyelle\n", tolower(c));
    }

    return 0 ;
}
*/
int  main()
{
    char c;
    int test = 1;
    printf("ENTRER UN CARACTERE: ");
    scanf("%s", &c);
    c = toupper(c);
    switch (c)
    {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'Y':
        printf("Le caractère %c est une voyelle \n", tolower(c));
        break;
    
    default:
        printf("Le caractère %c n'est pas une voyelle\n", tolower(c));
        break;
    }

    return 0 ;
}

