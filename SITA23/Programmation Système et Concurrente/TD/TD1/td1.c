#include <fcntl.h>   // pour open()
#include <unistd.h>  // pour write() et close()
#include <string.h>  // pour strlen()
#include <stdio.h>   // pour perror

void programme(char* nomfic_source, char* nomfic_dest) {
    int fd_source, fd_dest;
    int delta = 'a' - 'A';

    // Ouvrir le fichier source en lecture seule
    fd_source = open(nomfic_source, O_RDONLY);
    if (fd_source == -1) {
        perror("Erreur lors de l'ouverture du fichier source");
        return;
    }

    // Ouvrir ou créer le fichier de destination en écriture
    fd_dest = open(nomfic_dest, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd_dest == -1) {
        perror("Erreur lors de l'ouverture du fichier de destination");
        close(fd_source);
        return;
    }

    char buffer[1024];
    int nbLus;

    // Lire le fichier source, transformer les caractères et écrire dans le fichier de destination
    while ((nbLus = read(fd_source, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < nbLus; i++) {
            buffer[i] -= delta;
        }
        if (write(fd_dest, buffer, nbLus) == -1) {
            perror("Erreur lors de l'écriture dans le fichier de destination");
            close(fd_source);
            close(fd_dest);
            return;
        }
    }

    close(fd_source);
    close(fd_dest);
}

int main(void) {
    programme("ficTD1.txt", "fic_Maj.txt");
    return 0;
}