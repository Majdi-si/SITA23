#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <stdint.h>

#define TAILLE_BUFFER 30
#define LONGUEUR_MESSAGE 100

// Buffer partagé et sémaphores
char buffer[TAILLE_BUFFER][LONGUEUR_MESSAGE]; // Buffer partagé entre les threads
sem_t sem_vide; // Sémaphore pour les emplacements vides
sem_t sem_plein; // Sémaphore pour les emplacements pleins
pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER; // Mutex pour protéger l'accès au buffer
int index_ecriture = 0; // Index d'écriture dans le buffer
int index_lecture = 0; // Index de lecture dans le buffer

// Prototypes de fonctions
void* tache_capteur(void* arg);
void* tache_journal(void* arg);

int main() {
    pthread_t thread_capteur1, thread_capteur2, thread_journal;

    // Initialiser les sémaphores
    sem_init(&sem_vide, 0, TAILLE_BUFFER); // Tous les emplacements sont initialement vides
    sem_init(&sem_plein, 0, 0); // Aucun emplacement n'est initialement plein

    // Créer des threads pour les capteurs et le journal
    pthread_create(&thread_capteur1, NULL, tache_capteur, (void*)(intptr_t)1);
    pthread_create(&thread_capteur2, NULL, tache_capteur, (void*)(intptr_t)2);
    pthread_create(&thread_journal, NULL, tache_journal, NULL);

    // Joindre les threads (dans une application réelle, nous gérerions correctement la terminaison)
    pthread_join(thread_capteur1, NULL);
    pthread_join(thread_capteur2, NULL);
    pthread_join(thread_journal, NULL);

    // Détruire les sémaphores
    sem_destroy(&sem_vide);
    sem_destroy(&sem_plein);

    return 0;
}

void* tache_capteur(void* arg) {
    int id_capteur = (intptr_t)arg; // Identifiant du capteur
    char nom_fichier[20];
    snprintf(nom_fichier, sizeof(nom_fichier), "donnees%d.txt", id_capteur); // Nom du fichier de données du capteur

    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier de données du capteur");
        pthread_exit(NULL);
    }

    char valeur[LONGUEUR_MESSAGE];
    while (fgets(valeur, sizeof(valeur), fichier) != NULL) { // Lire les valeurs du fichier
        // Limiter la longueur de la chaîne valeur pour éviter la troncature
        valeur[strcspn(valeur, "\n")] = 0; // Supprimer le caractère de nouvelle ligne
        char message[LONGUEUR_MESSAGE];
        snprintf(message, sizeof(message), "Capteur %d : %.80s", id_capteur, valeur); // Formater le message

        sem_wait(&sem_vide); // Attendre un emplacement vide
        pthread_mutex_lock(&mutex_buffer); // Verrouiller le mutex

        strncpy(buffer[index_ecriture], message, LONGUEUR_MESSAGE); // Copier le message dans le buffer
        index_ecriture = (index_ecriture + 1) % TAILLE_BUFFER; // Avancer l'index d'écriture

        pthread_mutex_unlock(&mutex_buffer); // Déverrouiller le mutex
        sem_post(&sem_plein); // Signaler qu'un emplacement est plein

        usleep(100); // Attendre un peu avant de lire la prochaine valeur
    }

    fclose(fichier);
    pthread_exit(NULL);
}

void* tache_journal(void* arg) {
    (void)arg; // Supprimer l'avertissement de paramètre inutilisé
    while (1) {
        sem_wait(&sem_plein); // Attendre un emplacement plein
        pthread_mutex_lock(&mutex_buffer); // Verrouiller le mutex

        FILE* fichier = fopen("log.txt", "a"); // Ouvrir le fichier journal en mode append
        if (fichier == NULL) {
            perror("Erreur lors de l'ouverture du fichier journal");
            pthread_mutex_unlock(&mutex_buffer);
            pthread_exit(NULL);
        }

        fputs(buffer[index_lecture], fichier); // Écrire le contenu du buffer dans le fichier journal
        fclose(fichier); // Fermer le fichier pour forcer l'écriture sur le disque

        index_lecture = (index_lecture + 1) % TAILLE_BUFFER; // Avancer l'index de lecture

        pthread_mutex_unlock(&mutex_buffer); // Déverrouiller le mutex
        sem_post(&sem_vide); // Signaler qu'un emplacement est vide
    }

    pthread_exit(NULL);
}