#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define TAILLE_BUFFER 256

// Buffer partagé et primitives de synchronisation
char buffer[TAILLE_BUFFER];
pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_buffer = PTHREAD_COND_INITIALIZER;
int buffer_pret = 0;

// Prototypes de fonctions
void* tache_capteur(void* arg);
void* tache_journal(void* arg);

int main() {
    pthread_t thread_capteur1, thread_capteur2, thread_journal;

    // Créer des threads pour les capteurs et le journal
    pthread_create(&thread_capteur1, NULL, tache_capteur, (void*)1);
    pthread_create(&thread_capteur2, NULL, tache_capteur, (void*)2);
    pthread_create(&thread_journal, NULL, tache_journal, NULL);

    // Joindre les threads (dans une application réelle, nous gérerions correctement la terminaison)
    pthread_join(thread_capteur1, NULL);
    pthread_join(thread_capteur2, NULL);
    pthread_join(thread_journal, NULL);

    return 0;
}

void* tache_capteur(void* arg) {
    int id_capteur = (int)arg;
    char nom_fichier[20];
    sprintf(nom_fichier, "donnees%d.txt", id_capteur);

    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier de données du capteur");
        pthread_exit(NULL);
    }

    char valeur[100];
    while (fgets(valeur, sizeof(valeur), fichier) != NULL) {
        char message[TAILLE_BUFFER];
        sprintf(message, "Capteur %d : %s", id_capteur, valeur);

        pthread_mutex_lock(&mutex_buffer);
        while (buffer_pret) {
            pthread_cond_wait(&cond_buffer, &mutex_buffer);
        }
        strncpy(buffer, message, TAILLE_BUFFER);
        buffer_pret = 1;
        pthread_cond_signal(&cond_buffer);
        pthread_mutex_unlock(&mutex_buffer);

        usleep(100);
    }

    fclose(fichier);
    pthread_exit(NULL);
}

void* tache_journal(void* arg) {
    FILE* fichier = fopen("log.txt", "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier journal");
        pthread_exit(NULL);
    }

    while (1) {
        pthread_mutex_lock(&mutex_buffer);
        while (!buffer_pret) {
            pthread_cond_wait(&cond_buffer, &mutex_buffer);
        }
        fputs(buffer, fichier);
        fflush(fichier);
        buffer_pret = 0;
        pthread_cond_signal(&cond_buffer);
        pthread_mutex_unlock(&mutex_buffer);
    }

    fclose(fichier);
    pthread_exit(NULL);
}