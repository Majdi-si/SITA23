#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *foncThread(void *arg) {
    int thread_num = *((int *)arg);
    for(int i = 0; i < 10; i++) {
        printf("Thread %d : affichage numéro %d\n", thread_num, i);
    }
    return 0;
}

int main(void) {
    pthread_t idThread1, idThread2, idThread3;
    int thread_num1 = 1, thread_num2 = 2, thread_num3 = 3;

    pthread_create(&idThread1, NULL, foncThread, &thread_num1);
    pthread_create(&idThread2, NULL, foncThread, &thread_num2);
    pthread_create(&idThread3, NULL, foncThread, &thread_num3);

    pthread_join(idThread1, NULL);
    pthread_join(idThread2, NULL);
    pthread_join(idThread3, NULL);

    return 0;
}
