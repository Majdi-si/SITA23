#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void){
    int status, tube[2], nb, pid1, pid2;
    char buf[512];
    pipe(tube);
    if (pid1 = fork() == 0){
        close(tube[0]);
        int fd;
        if ((fd = open("donnees1.txt", O_RDONLY)) == -1) {
            perror("Erreur ouverture fichier");
            exit(1);
        }
        while ((nb = read(fd, buf, sizeof(buf))) > 0) {
            write(tube[1], buf, nb);
        }
        close(fd);
        close(tube[1]);
        exit(0);
    }
    if(pid2 = fork() == 0){
        close(tube[0]);
        int fd;
        if ((fd = open("donnees2.txt", O_RDONLY)) == -1) {
            perror("Erreur ouverture fichier");
            exit(1);
        }
        while ((nb = read(fd, buf, sizeof(buf))) > 0) {
            write(tube[1], buf, nb);
        }
        close(fd);
        close(tube[1]);
        exit(0);
    }
    else{
        close(tube[1]);
        while ((nb = read(tube[0], buf, sizeof(buf))) > 0) {
            write(1, buf, nb);
        }
        close(tube[0]);
        exit(0);
    }
    close(tube[0]);
    close(tube[1]);
    wait(&status);
    wait(&status);
    return 0;
}