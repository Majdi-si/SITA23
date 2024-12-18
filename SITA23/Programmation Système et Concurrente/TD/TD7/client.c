#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

int main() {
    int sock;
    struct sockaddr_in sin;
    struct hostent *host;
    char nomMachine[256];
    char message[] = "Hello, Server!";
    FILE *file;
    char buffer[1024];
    size_t bytesRead;

    // Création de la socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("erreur socket()");
        exit(0);
    }

    // Récupération du nom de la machine locale
    if (gethostname(nomMachine, sizeof(nomMachine)) == -1) {
        perror("erreur gethostname()");
        close(sock);
        exit(0);
    }

    printf("Le nom de la machine locale est : %s\n", nomMachine);

    // Récupération de l'IP à partir du nom de machine
    if ((host = gethostbyname(nomMachine)) == NULL) {
        perror("erreur gethostbyname()");
        close(sock);
        exit(0);
    }

    memcpy(&(sin.sin_addr.s_addr), host->h_addr_list[0], sizeof(unsigned long));
    //sin.sin_addr.s_addr = inet_addr("192.168.193.9");  // en loopback pour test
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9999); // port 9999

    // Connexion
    if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) == -1) {
        perror("erreur connect()");
        close(sock);
        exit(0);
    }

    printf("Connexion effectuée\n");

    // Emission du message sur la socket
    if (send(sock, message, strlen(message) + 1, 0) == -1) {
        perror("erreur send()");
        close(sock);
        exit(0);
    }

    printf("Message envoyé : %s\n", message);

    // Ouverture du fichier en lecture
    file = fopen("donnees3.txt", "r");
    if (file == NULL) {
        perror("erreur fopen()");
        close(sock);
        exit(0);
    }

    // Lecture et envoi du contenu du fichier
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (send(sock, buffer, bytesRead, 0) == -1) {
            perror("erreur send()");
            fclose(file);
            close(sock);
            exit(0);
        }
    }

    // Fermeture du fichier
    fclose(file);

    // Fermeture de la socket
    close(sock);

    return 0;
}