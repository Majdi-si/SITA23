#include <stdio.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

/**********************************************************************
		Exemple code serveur socket

**********************************************************************/

#define BUF_SIZE 20

int main (void) {

	int sock, csock;
	struct sockaddr_in sin, csin;
	int nbRecus;
	socklen_t taille;
	char buf [BUF_SIZE];


	// Creation de la socket d ecoute

	if ((sock = socket(AF_INET, SOCK_STREAM, 0))==-1) {
		perror("erreur socket()");
		exit(0);
	}

	// attachement de la socket (toute connexions entrantes acceptees, ecoute sur le port 9999)

	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(9999); /* port 9999 */

	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
		perror("erreur bind()");
		close(sock);
		exit(0);
	}

	// sock devient une socket d'écoute, une seule connexion a la fois

	if (listen(sock, 1)!=0) {
		perror("erreur listen()");
		close(sock);
		exit(0);
	}

	while(1) { // serveur en boucle infinie d'attente de connexions client : traite un client après l'autre
	
		taille = sizeof(csin);

		// attente d une connexion client

		if ((csock=accept(sock, (struct sockaddr *)&csin, &taille)) == -1){
			perror("erreur accept()");
			close(sock);
			exit(0);
		}

		// lecture des informations recues (sur csock)

		if ((nbRecus=recv(csock, buf, BUF_SIZE, 0))<=0){
			perror("erreur recv()");
			close(sock);
			exit(0);
		}

		// affichage des informations recues

		write(1, buf, nbRecus);
		
	} // fin while 1

	return 0;

}
/*-------------------------------------------------------------------------------------*/