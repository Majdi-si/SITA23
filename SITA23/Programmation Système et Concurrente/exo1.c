#include <fcntl.h>	// pour open()
#include <unistd.h>	// pour write() et close()
#include <string.h>	// pour strlen()

int main (void){
int fd, nbEcr, taille;

/* Ouverture du fichier toto.txt en ecriture. 
   - Le curseur de position courante dans le fichier est place a la fin (flag O_APPEND). 
     Ce qui va etre ecrit sera donc rajoute au contenu precedent du fichier */

fd = open("toto.txt", O_WRONLY|O_APPEND);

/* Ecriture de la chaine de caractere " il fait beau !\n" dans le fichier toto.txt */
taille = strlen(" il fait beau !\n");
nbEcr = write(fd, " il fait beau !\n", taille);

/* Fermeture du fichier toto.txt */
close(fd);

return 0;
} 	