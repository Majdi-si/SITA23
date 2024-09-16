#include <stdio.h>

int main (void) {
    char ch[10];
    puts("Donne des caractères :");
    scanf("%5[^\n]", ch);
    printf("Les caractères sont: %s \n", ch);
    return 0;
}