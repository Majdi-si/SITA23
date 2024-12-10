#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define CLE_MEM_PARTAGEE 0x1234
#define TAILLE_MEM_PARTAGEE sizeof(struct donnees_partagees)

struct donnees_partagees {
    int champ1;
    int champ2;
    int champ3;
};

int main() {
    int id_mem_partagee;
    struct donnees_partagees *ptr_mem_partagee;

    // Créer le segment de mémoire partagée
    id_mem_partagee = shmget(CLE_MEM_PARTAGEE, TAILLE_MEM_PARTAGEE, 0666);
    if (id_mem_partagee == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attacher le segment de mémoire partagée à notre espace d'adressage
    ptr_mem_partagee = (struct donnees_partagees *)shmat(id_mem_partagee, NULL, 0);
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
    if (shmctl(id_mem_partagee, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}