
#include <stdio.h>
int  main()
{
    char c;
    int i;
    printf("ENTRER UN CARACTERE: ");
    scanf("%s", &c);
    printf("VOICI SON CODE ASCII: %d\n",c);
    printf("VOICI SON CODE ASCII EN HEXADECIMAL: %x\n",c);
    printf("ENTRER UN NOMBRE: ");
    scanf("%d", &i);
    printf("VOICI CE NOMBRE EN HEXADECIMAL: %x\n",i);

    return 0 ;
}
