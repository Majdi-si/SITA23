/* IPC: Memoire partagee - applicationTD5.c */

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

struct infoAppli {
    pid_t pid;	/* le pid du processus */
    char message [80];	/* un texte informatif */
    float valeur;	/* le résultat intermédiaire du calcul */
};

int id;
struct infoAppli *adresse;  /* adresse du segment de memoire partagee */

void gest_sigusr1(int sig) {
    /* Detachement de la zone de memoire partagee */
    if (shmdt(adresse) == -1) {
        perror("Detachement memoire partagee");
    }

    /* Destruction de la zone de memoire partagee */
    if (shmctl(id, IPC_RMID, NULL) == -1) {
        perror("Destruction memoire partagee");
    }

    printf("Fin de l'application\n");
    exit(0);
}

int main(void) {
    int cle;
    int i = 0;

    /* Tirage de cle */
    if ((cle = ftok("td6-2", 1)) == -1) {
        perror("ftok");
        exit(1);
    }

    /* Creation d'un segment de memoire partagee de la taille de la structure */
    if ((id = shmget(cle, sizeof(struct infoAppli), 0600 | IPC_CREAT)) == -1) {
        perror("Creation memoire partagee");
        exit(1);
    }

    /* Attachement de la zone de memoire a l'espace memoire du processus */
    if ((long)(adresse = shmat(id, NULL, 0)) == -1) {
        perror("Attachement memoire partagee");
        shmctl(id, IPC_RMID, NULL);  /* Suppression du segment */
        exit(1);
    }

    /* Installation du gestionnaire de signal pour SIGUSR1 */
    signal(SIGUSR1, gest_sigusr1);

    srand(time(NULL));
    while (1) {
        adresse->pid = getpid();
        sprintf(adresse->message, "Message numero %d", i);
        adresse->valeur = rand() % 100 + (float)(rand() % 1000) / 1000.0;
        i++;
        sleep(10);
    }

    return 0;
}
