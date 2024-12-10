#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>


struct donnees_partagees {
    int champ1;
    int champ2;
    int champ3;
};

int main() {
    struct donnees_partagees *ptr_mem_partagee;
    int cle, id;

    /* Tirage de cle */

  if ((cle=ftok("applicationTD6", 1))==-1){
    perror("ftok");
    exit(1);
  }

    // Créer le segment de mémoire partagée
  if ((id = shmget(cle, sizeof(struct donnees_partagees), 0600|IPC_CREAT))==-1) {
    perror("Creation memoire partagee");
    exit(1);
  }

    // Attacher le segment de mémoire partagée à notre espace d'adressage
    ptr_mem_partagee = (struct donnees_partagees *)shmat(id, NULL, 0);
    if (ptr_mem_partagee == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Afficher les valeurs des 3 champs
    printf("Champ1: %d\n", ptr_mem_partagee->champ1);
    printf("Champ2: %d\n", ptr_mem_partagee->champ2);
    printf("Champ3: %d\n", ptr_mem_partagee->champ3);

    // Détacher le segment de mémoire partagée
    if (shmdt(ptr_mem_partagee) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Supprimer le segment de mémoire partagée
    if (shmctl(id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}