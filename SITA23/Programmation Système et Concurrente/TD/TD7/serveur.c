#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock, client_sock;
    struct sockaddr_in sin, client_sin;
    socklen_t client_sin_len = sizeof(client_sin);
    char buffer[1024];
    int received;

    // Création de la socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("erreur socket()");
        exit(0);
    }

    // Configuration de l'adresse du serveur
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(9999);

    // Liaison de la socket à l'adresse du serveur
    if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) == -1) {
        perror("erreur bind()");
        close(sock);
        exit(0);
    }

    // Mise en écoute des connexions entrantes
    if (listen(sock, 5) == -1) {
        perror("erreur listen()");
        close(sock);
        exit(0);
    }

    printf("Serveur en attente de connexion sur le port 9999...\n");

    while (1) {
        // Acceptation d'une connexion entrante
        if ((client_sock = accept(sock, (struct sockaddr*)&client_sin, &client_sin_len)) == -1) {
            perror("erreur accept()");
            close(sock);
            exit(0);
        }

        printf("Connexion acceptée\n");

        // Lecture des données envoyées par le client
        while ((received = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
            buffer[received] = '\0';
            printf("Reçu: %s\n", buffer);
        }

        if (received == -1) {
            perror("erreur recv()");
        } else {
            printf("Connexion fermée par le client\n");
        }

        // Fermeture de la socket client
        close(client_sock);
    }

    // Fermeture de la socket serveur
    close(sock);

    return 0;
}