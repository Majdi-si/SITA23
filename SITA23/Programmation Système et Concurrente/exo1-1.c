#include <fcntl.h>   // pour open()
#include <unistd.h>  // pour write() et close()
#include <string.h>  // pour strlen()
#include <stdio.h>   // pour perror

int main(void) {
    int fd, nbEcr, taille;

    /* Ouverture du fichier toto.txt en écriture.
       - Le fichier est créé s'il n'existe pas (flag O_CREAT).
       - Le curseur de position courante dans le fichier est placé à la fin (flag O_APPEND). */

    fd = open("toto1-1.txt", O_WRONLY | O_CREAT | O_APPEND, 0600);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    /* Écriture de la chaîne de caractères " il fait pas beau !\n" dans le fichier toto.txt */
    taille = strlen(" Bonjour !\n");
    nbEcr = write(fd, " Bonjour !\n", taille);
    if (nbEcr == -1) {
        perror("Erreur lors de l'écriture dans le fichier");
        close(fd);
        return 1;
    }

    /* Fermeture du fichier toto.txt */
    if (close(fd) == -1) {
        perror("Erreur lors de la fermeture du fichier");
        return 1;
    }

    return 0;
}