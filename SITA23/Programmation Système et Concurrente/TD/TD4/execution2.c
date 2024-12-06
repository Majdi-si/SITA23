#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd, nb;
    char buf[512];

    if ((fd = open("donnees2.txt", O_RDONLY)) == -1) {
        perror("Erreur ouverture fichier");
        exit(1);
    }

    while ((nb = read(fd, buf, sizeof(buf))) > 0) {
        write(1, buf, nb);
    }

    close(fd);
    return 0;
}