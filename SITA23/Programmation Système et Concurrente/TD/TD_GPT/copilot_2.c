#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PAQUETS 10
#define MAX_COLIS 5

int paquets = 0;
int colis = 0;
int bureau_ouvert = 1;

pthread_mutex_t mutex_paquets = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_colis = PTHREAD_MUTEX_INITIALIZER;
sem_t chariot;
sem_t client;
pthread_cond_t P_plein = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex_P_plein = PTHREAD_MUTEX_INITIALIZER;

void* tache_principale(void* arg) {
    (void)arg;
    while (1) {
        pthread_mutex_lock(&mutex_P_plein);
        pthread_cond_wait(&P_plein, &mutex_P_plein);
        pthread_mutex_unlock(&mutex_P_plein);

        sem_wait(&chariot);
        bureau_ouvert = 0;
        printf("Bureau fermé par la tache principale\n");
        sem_post(&chariot);
    }
    return NULL;
}

void* tache_client(void* arg) {
    (void)arg;
    while (bureau_ouvert) {
        sem_wait(&client);
        printf("Client est arrivé\n");
        sleep(1); // Simule le temps de traitement
    }
    return NULL;
}

void* tache_personneA(void* arg) {
    (void)arg;
    while (bureau_ouvert) {
        sem_wait(&client);
        sem_wait(&chariot);
        pthread_mutex_lock(&mutex_paquets);
        if (paquets >= MAX_PAQUETS) {
            bureau_ouvert = 0;
            pthread_cond_signal(&P_plein);
            printf("Stockage de paquets plein, fermeture du bureau\n");
        } else {
            paquets++;
            printf("Personne A dépose un paquet, total paquets: %d\n", paquets);
        }
        pthread_mutex_unlock(&mutex_paquets);
        sem_post(&chariot);
        sleep(1); // Simule le temps de traitement
    }
    return NULL;
}

void* tache_personneB(void* arg) {
    (void)arg;
    while (bureau_ouvert) {
        sem_wait(&client);
        sem_wait(&chariot);
        pthread_mutex_lock(&mutex_colis);
        if (colis == 0) {
            printf("Personne B attend le livreur\n");
        } else {
            colis--;
            printf("Personne B prend un colis, total colis: %d\n", colis);
        }
        pthread_mutex_unlock(&mutex_colis);
        sem_post(&chariot);
        sleep(1); // Simule le temps de traitement
    }
    return NULL;
}

void* tache_livreur(void* arg) {
    (void)arg;
    while (bureau_ouvert) {
        pthread_mutex_lock(&mutex_colis);
        if (colis < MAX_COLIS) {
            colis++;
            printf("Livreur dépose un colis, total colis: %d\n", colis);
        }
        pthread_mutex_unlock(&mutex_colis);
        sleep(1); // Simule le temps de traitement
    }
    return NULL;
}

int main() {
    pthread_t thread_principal, thread_client, thread_personneA, thread_personneB, thread_livreur;

    sem_init(&chariot, 0, 1);
    sem_init(&client, 0, 1);

    pthread_create(&thread_principal, NULL, tache_principale, NULL);
    pthread_create(&thread_client, NULL, tache_client, NULL);
    pthread_create(&thread_personneA, NULL, tache_personneA, NULL);
    pthread_create(&thread_personneB, NULL, tache_personneB, NULL);
    pthread_create(&thread_livreur, NULL, tache_livreur, NULL);

    pthread_join(thread_principal, NULL);
    pthread_join(thread_client, NULL);
    pthread_join(thread_personneA, NULL);
    pthread_join(thread_personneB, NULL);
    pthread_join(thread_livreur, NULL);

    sem_destroy(&chariot);
    sem_destroy(&client);
    pthread_mutex_destroy(&mutex_paquets);
    pthread_mutex_destroy(&mutex_colis);
    pthread_cond_destroy(&P_plein);

    return 0;
}