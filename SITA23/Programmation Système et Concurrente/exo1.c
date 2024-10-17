#include <fcntl.h>	// pour open()
#include <unistd.h>	// pour write() et close()
#include <string.h>	// pour strlen()
#include <stdio.h> //pour perror

int main (void){
int fd, nbEcr, taille;

/* Ouverture du fichier toto.txt en ecriture. 
   - Le curseur de position courante dans le fichier est place a la fin (flag O_APPEND). 
     Ce qui va etre ecrit sera donc rajoute au contenu precedent du fichier */

fd = open("toto.txt", O_WRONLY|O_APPEND);
if (fd == -1) {
    perror("Erreur lors de l'ouverture du fichier");
    return 1;
}

/* Ecriture de la chaine de caractere " il fait beau !\n" dans le fichier toto.txt */
taille = strlen(" il fait beau !\n");
nbEcr = write(fd, " il fait beau !\n", taille);
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