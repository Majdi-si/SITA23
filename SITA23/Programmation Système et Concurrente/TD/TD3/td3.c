#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define TAILLE_BUFFER 30
#define LONGUEUR_MESSAGE 100

// Buffer partagé et primitives de synchronisation
char buffer[TAILLE_BUFFER][LONGUEUR_MESSAGE]; // Buffer partagé entre les threads
pthread_mutex_t mutex_buffer = PTHREAD_MUTEX_INITIALIZER; // Mutex pour protéger l'accès au buffer
pthread_cond_t cond_buffer = PTHREAD_COND_INITIALIZER; // Condition pour signaler les changements d'état du buffer
int buffer_pret[TAILLE_BUFFER] = {0}; // Indicateur de l'état du buffer (0 = vide, 1 = prêt)
int index_ecriture = 0; // Index d'écriture dans le buffer
int index_lecture = 0; // Index de lecture dans le buffer

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
    int id_capteur = (int)arg; // Identifiant du capteur
    char nom_fichier[20];
    sprintf(nom_fichier, "donnees%d.txt", id_capteur); // Nom du fichier de données du capteur

    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier de données du capteur");
        pthread_exit(NULL);
    }

    char valeur[LONGUEUR_MESSAGE];
    while (fgets(valeur, sizeof(valeur), fichier) != NULL) { // Lire les valeurs du fichier
        char message[LONGUEUR_MESSAGE];
        sprintf(message, "Capteur %d : %s", id_capteur, valeur); // Formater le message

        pthread_mutex_lock(&mutex_buffer); // Verrouiller le mutex
        while (buffer_pret[index_ecriture]) { // Attendre que l'emplacement du buffer soit vide
            pthread_cond_wait(&cond_buffer, &mutex_buffer);
        }
        strncpy(buffer[index_ecriture], message, LONGUEUR_MESSAGE); // Copier le message dans le buffer
        buffer_pret[index_ecriture] = 1; // Indiquer que l'emplacement du buffer est prêt
        index_ecriture = (index_ecriture + 1) % TAILLE_BUFFER; // Avancer l'index d'écriture
        pthread_cond_signal(&cond_buffer); // Signaler que le buffer est prêt
        pthread_mutex_unlock(&mutex_buffer); // Déverrouiller le mutex

        usleep(100); // Attendre un peu avant de lire la prochaine valeur
    }

    fclose(fichier);
    pthread_exit(NULL);
}

void* tache_journal(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex_buffer); // Verrouiller le mutex
        while (!buffer_pret[index_lecture]) { // Attendre que l'emplacement du buffer soit prêt
            pthread_cond_wait(&cond_buffer, &mutex_buffer);
        }

        FILE* fichier = fopen("log.txt", "a"); // Ouvrir le fichier journal en mode append
        if (fichier == NULL) {
            perror("Erreur lors de l'ouverture du fichier journal");
            pthread_mutex_unlock(&mutex_buffer);
            pthread_exit(NULL);
        }

        fputs(buffer[index_lecture], fichier); // Écrire le contenu du buffer dans le fichier journal
        fclose(fichier); // Fermer le fichier pour forcer l'écriture sur le disque

        buffer_pret[index_lecture] = 0; // Indiquer que l'emplacement du buffer est vide
        index_lecture = (index_lecture + 1) % TAILLE_BUFFER; // Avancer l'index de lecture
        pthread_cond_signal(&cond_buffer); // Signaler que le buffer est vide
        pthread_mutex_unlock(&mutex_buffer); // Déverrouiller le mutex
    }

    pthread_exit(NULL);
}