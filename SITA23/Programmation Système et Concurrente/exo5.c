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
pthread_cond_t cond_vide = PTHREAD_COND_INITIALIZER; // Condition pour les emplacements vides
pthread_cond_t cond_plein = PTHREAD_COND_INITIALIZER; // Condition pour les emplacements pleins
pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER; // Mutex pour protéger l'accès au buffer
int index_ecriture = 0; // Index d'écriture dans le buffer
int index_lecture = 0; // Index de lecture dans le buffer
int count = 0; // Nombre d'éléments dans le buffer
int terminer = 0; // Indicateur pour terminer les threads

// Prototypes de fonctions
void* tache_capteur(void* arg);
void* tache_journal(void* arg);

int main() {
    pthread_t thread_capteur1, thread_capteur2, thread_journal;

    pthread_cond_init(&cond_vide, NULL); // Initialiser la condition pour les emplacements vides
    pthread_cond_init(&cond_plein, NULL); // Initialiser la condition pour les emplacements pleins

    // Créer des threads pour les capteurs et le journal
    pthread_create(&thread_capteur1, NULL, tache_capteur, (void*)(intptr_t)1);
    pthread_create(&thread_capteur2, NULL, tache_capteur, (void*)(intptr_t)2);
    pthread_create(&thread_journal, NULL, tache_journal, NULL);

    // Joindre les threads (dans une application réelle, nous gérerions correctement la terminaison)
    pthread_join(thread_capteur1, NULL);
    pthread_join(thread_capteur2, NULL);
    pthread_join(thread_journal, NULL);

    // Détruire les variables conditionnelles 
    pthread_cond_destroy(&cond_vide);
    pthread_cond_destroy(&cond_plein);

    return 0;
}

void* tache_capteur(void* arg) {
    int id_capteur = (intptr_t)arg; // Identifiant du capteur
    char nom_fichier[20];
    snprintf(nom_fichier, sizeof(nom_fichier), "donnees%d.txt", id_capteur); // Nom du fichier de données 
    //snprintf : permet de formater une chaîne de caractères et de la stocker dans un tableau de caractères

    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier de données du capteur");
        pthread_exit(NULL);
    }

    char valeur[LONGUEUR_MESSAGE];
    while (fgets(valeur, sizeof(valeur), fichier) != NULL) { // Lire les valeurs du fichier

        // Limiter la longueur de la chaîne valeur pour éviter la troncature
        valeur[strcspn(valeur, "\n")] = 0; // Supprimer le caractère de nouvelle ligne
        //strcspn : renvoie le nombre de caractères avant le premier caractère de la chaîne qui est présent dans la chaîne de recherche
        char message[LONGUEUR_MESSAGE];
        snprintf(message, sizeof(message), "Capteur %d : %.80s", id_capteur, valeur); // Message à écrire dans le journal

        pthread_mutex_lock(&mutex_buffer);
        while (count == TAILLE_BUFFER) { // Attendre un emplacement vide
            pthread_cond_wait(&cond_vide, &mutex_buffer);
        }

        strncpy(buffer[index_ecriture], message, LONGUEUR_MESSAGE); // Copier le message dans le buffer
        index_ecriture = (index_ecriture + 1) % TAILLE_BUFFER; // Avancer l'index d'écriture
        count++;

        pthread_cond_signal(&cond_plein); // Signaler qu'un emplacement est plein
        pthread_mutex_unlock(&mutex_buffer);

        usleep(100); // Attendre un peu avant de lire la prochaine valeur en microsecondes
    
    }
    terminer = 1;
    fclose(fichier);
    pthread_exit(NULL);
}

void* tache_journal(void* arg) {
    (void)arg; // Supprimer l'avertissement de paramètre inutilisé
    while (terminer == 0 ||  count > 0) {
        pthread_mutex_lock(&mutex_buffer);
        while (count == 0) { // Attendre un emplacement plein
            pthread_cond_wait(&cond_plein, &mutex_buffer);
        }

        FILE* fichier = fopen("log.txt", "a"); // Ouvrir le fichier journal en mode append
        if (fichier == NULL) {
            perror("Erreur lors de l'ouverture du fichier journal");
            pthread_mutex_unlock(&mutex_buffer);
            pthread_exit(NULL);
        }

        fputs(buffer[index_lecture], fichier); // Écrire le contenu du buffer dans le fichier journal
        fclose(fichier); // Fermer le fichier pour forcer l'écriture sur le disque

        index_lecture = (index_lecture + 1) % TAILLE_BUFFER; // Avancer l'index de lecture
        count--;

        pthread_cond_signal(&cond_vide); // Signaler qu'un emplacement est vide
        pthread_mutex_unlock(&mutex_buffer);
    }

    pthread_exit(NULL);
}