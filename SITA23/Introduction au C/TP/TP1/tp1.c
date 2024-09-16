#include <stdio.h>

void nombre_parfait(){
    int i;
    int n = 2;
    int somme = 1;
    for (int i =2; i<=10000; i++){
        for(n=2; n< i/2; n++){
            if (i%n==0){
                somme += n;
            }
        }
        if (somme == i){
            printf("Le nombre %d est un nombre parfait", i);
        }
        somme = 2;
    }
}

int main(){

    nombre_parfait();


    return 0;
}