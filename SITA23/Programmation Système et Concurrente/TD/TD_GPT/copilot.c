#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PAQUETS 10
#define MAX_COLIS 10

sem_t chariot;
sem_t stockage_paquets;
sem_t stockage_colis;
pthread_mutex_t mutex_paquets = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_colis = PTHREAD_MUTEX_INITIALIZER;

int paquets = 0;
int colis = 9;
int bureau_ouvert = 1;

void* tache_principale(void* arg) {
    (void)arg;
    printf("Bureau ouvert\n");
    sleep(10); // Simule la journée de travail
    bureau_ouvert = 0;
    printf("Bureau fermé\n");
    return NULL;
}

void* client(void* arg) {
    (void)arg;
    while (bureau_ouvert) {
        sem_wait(&chariot);
        printf("Client arrive\n");
        sem_post(&chariot);
        sleep(1); // Simule le temps entre les arrivées des clients
    }
    return NULL;
}

void* personneA(void* arg) {
    (void)arg;
    while (bureau_ouvert) {
        sem_wait(&chariot);
        pthread_mutex_lock(&mutex_paquets);
        if (paquets < MAX_PAQUETS) {
            paquets++;
            printf("Personne A dépose un paquet, total paquets: %d\n", paquets);
        } else {
            bureau_ouvert = 0;
            printf("Stockage de paquets plein, fermeture du bureau\n");
        }
        pthread_mutex_unlock(&mutex_paquets);
        sem_post(&chariot);
        sleep(1); // Simule le temps de traitement
    }
    return NULL;
}

void* personneB(void* arg) {
    (void)arg;
    while (bureau_ouvert) {
        sem_wait(&chariot);
        pthread_mutex_lock(&mutex_colis);
        if (colis > 0) {
            colis--;
            printf("Personne B donne un colis, total colis: %d\n", colis);
        }
        pthread_mutex_unlock(&mutex_colis);
        sem_post(&chariot);
        sleep(1); // Simule le temps de traitement
    }
    return NULL;
}

void* livreur(void* arg) {
    (void)arg;
    while (bureau_ouvert) {
        pthread_mutex_lock(&mutex_colis);
        if (colis < MAX_COLIS) {
            colis++;
            printf("Livreur dépose un colis, total colis: %d\n", colis);
        }
        pthread_mutex_unlock(&mutex_colis);
        sleep(2); // Simule le temps entre les livraisons
    }
    return NULL;
}

int main() {
    pthread_t tache_principale_thread, client_thread, personneA_thread, personneB_thread, livreur_thread;

    sem_init(&chariot, 0, 1);
    sem_init(&stockage_paquets, 0, MAX_PAQUETS);
    sem_init(&stockage_colis, 0, MAX_COLIS);

    pthread_create(&tache_principale_thread, NULL, tache_principale, NULL);
    pthread_create(&client_thread, NULL, client, NULL);
    pthread_create(&personneA_thread, NULL, personneA, NULL);
    pthread_create(&personneB_thread, NULL, personneB, NULL);
    pthread_create(&livreur_thread, NULL, livreur, NULL);

    pthread_join(tache_principale_thread, NULL);
    pthread_join(client_thread, NULL);
    pthread_join(personneA_thread, NULL);
    pthread_join(personneB_thread, NULL);
    pthread_join(livreur_thread, NULL);

    sem_destroy(&chariot);
    sem_destroy(&stockage_paquets);
    sem_destroy(&stockage_colis);

    return 0;
}