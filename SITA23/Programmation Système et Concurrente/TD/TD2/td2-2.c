#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 256
#define NUM_ITERATIONS 50

sem_t sem_request;
sem_t sem_response;

char buffer[BUFFER_SIZE];
pthread_mutex_t buffer_mutex;

void* server_task(void* arg) {
    while (1) {
        sem_wait(&sem_request);  // Attente de la demande d'un client

        // Traiter la requête : ajouter l'horodatage
        char response[BUFFER_SIZE];
        time_t mytime = time(NULL);
        struct tm* time_info = localtime(&mytime);
        strftime(response, sizeof(response), "%d/%m/%y %I:%M:%S %p", time_info);

        // Ajout de l'horodatage dans le buffer
        pthread_mutex_lock(&buffer_mutex);
        strcat(buffer, " ");
        strcat(buffer, response);  // Ajout de l'horodatage au message
        pthread_mutex_unlock(&buffer_mutex);

        sem_post(&sem_response);  // Signale au client que la réponse est prête
    }
    return NULL;
}

void* client_task(void* arg) {
    int client_id = *((int*)arg);
    char message[BUFFER_SIZE];

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Placer le message dans le buffer
        pthread_mutex_lock(&buffer_mutex);
        sprintf(buffer, "Client %d request %d", client_id, i+1);  // Initialiser le buffer avec le message du client
        pthread_mutex_unlock(&buffer_mutex);

        sem_post(&sem_request);  // Demande au serveur de traiter la requête

        sem_wait(&sem_response);  // Attente de la réponse du serveur

        pthread_mutex_lock(&buffer_mutex);
        printf("Client %d received: %s\n", client_id, buffer);  // Affiche la réponse du serveur
        buffer[0] = '\0';  // Réinitialiser le buffer
        pthread_mutex_unlock(&buffer_mutex);

        sleep(1);  // Simuler un délai entre les requêtes
    }
    return NULL;
}

int main() {
    sem_init(&sem_request, 0, 0);
    sem_init(&sem_response, 0, 0);

    pthread_t server_thread;
    pthread_t client_threads[2];

    pthread_mutex_init(&buffer_mutex, NULL);

    pthread_create(&server_thread, NULL, server_task, NULL);
    pthread_create(&client_threads[0], NULL, client_task, (void*)&(int){1});
    pthread_create(&client_threads[1], NULL, client_task, (void*)&(int){2});

    pthread_join(client_threads[0], NULL);
    pthread_join(client_threads[1], NULL);

    pthread_cancel(server_thread);

    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&sem_request);
    sem_destroy(&sem_response);

    return 0;
}