#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

void nombre_parfait(){
    int i, n, somme;
    for (i = 2; i <= 10000; i++){
        somme = 1;
        int sqrt_i = (int)sqrt(i);
        for(n = 2; n <= sqrt_i; n++){
            if (i % n == 0){
                somme += n;
                if (n != i / n) {
                    somme += i / n;
                }
            }
        }
        if (somme == i){
            printf("Le nombre %d est un nombre parfait\n", i);
        }
    }
}

bool est_premier(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

void all_nombres_parfaits() {
    int n;
    for (n = 1; n <= 30; n++) {
        int a = (int)pow(2, n + 1) - 1; 
        if (est_premier(a)) {
            long long N = (long long)pow(2, n) * a; // N = 2^n * (2^(n+1) - 1)
            printf("Le nombre parfait pour n = %d est %lld\n", n, N);
        }
    }
}

void nombre_nombres_premiers(){
    int n;
    int somme = 0;
    printf("Entrez un nombre : ");
    scanf("%d",&n);
    for (int x = 1; x<=n; x++){
        if(est_premier(x)){
            somme ++;
        }
    }
    printf("Il y a %d nombres premiers entre 1 et %d \n", somme, n);
}

int main(){
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    nombre_nombres_premiers();
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Temps d'exécution: %f secondes\n", cpu_time_used);

    return 0;
}