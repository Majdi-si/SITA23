#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *foncThread1 (void *a) {
    (void)a;
    for(int i = 0; i<10; i++){
        printf("Thread 1 : affichage numéro %d\n", i);
    }
    return 0;
}

void *foncThread2 (void *a) {
    (void)a;
    for(int i = 0; i<10; i++){
        printf("Thread 2 : affichage numéro %d\n", i);
    }
    return 0;
}

void *foncThread3 (void *a) {
    (void)a;
    for(int i = 0; i<10; i++){
        printf("Thread 3 : affichage numéro %d\n", i);
    }
    return 0;
}


int main(void){
    pthread_t idThread1;
    pthread_t idThread2;
    pthread_t idThread3;

    if (pthread_create(&idThread1, NULL, foncThread1, NULL) != 0) {
        perror("Failed to create thread 1");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&idThread2, NULL, foncThread2, NULL) != 0) {
        perror("Failed to create thread 2");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&idThread3, NULL, foncThread3, NULL) != 0) {
        perror("Failed to create thread 3");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(idThread1, NULL) != 0) {
        perror("Failed to join thread 1");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(idThread2, NULL) != 0) {
        perror("Failed to join thread 2");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(idThread3, NULL) != 0) {
        perror("Failed to join thread 3");
        exit(EXIT_FAILURE);
    }
}

