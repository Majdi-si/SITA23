#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void){
    int pid1, pid2, status;
    if((pid1 = fork()) == 0){
        printf("Je suis le fils 1, mon pid est %d et celui de mon père est %d\n", getpid(), getppid());
        execl("./execution1", "execution1", NULL);
        perror("Erreur execl");
        exit(0);
    }
    if ((pid2 = fork()) == 0){
        printf("Je suis le fils 2, mon pid est %d et celui de mon père est %d\n", getpid(), getppid());
        execl("./execution2", "execution2", NULL);
        perror("Erreur execl");
        exit(0);
    }
    wait(&status);
    wait(&status);
    return 0;
}