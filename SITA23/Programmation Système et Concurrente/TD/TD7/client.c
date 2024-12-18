/**********************************************************************
		Exemple code client socket

**********************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main (void) {

    char *message = "Bonjour";
	char nomMachine[30];

	int sock;
	struct sockaddr_in sin;
	struct hostent *host;

	/* Creation d'une socket */

	if ((sock = socket(AF_INET, SOCK_STREAM, 0))==-1){
			perror("erreur socket()");
			exit(0);
	}

	/* On recupere le nom de la machine (pour test en local) */

	gethostname(nomMachine, 30);
	printf("Le nom de la machine locale est :%s: \n", nomMachine);

	/* On recupere l'IP a partir du nom de machine */

	if ((host=gethostbyname(nomMachine)) == NULL){
			perror("erreur gethostbyname()");
			close(sock);
			exit(0);
	}

	memcpy(&(sin.sin_addr.s_addr) , host->h_addr_list[0],sizeof(unsigned long));
	//sin.sin_addr.s_addr = inet_addr("127.0.0.1");  // en loopback pour test
	sin.sin_family = AF_INET;
	sin.sin_port = htons(9999); /* port 9999 */

	/* Connexion */

	if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) == -1){
			perror("erreur connect()");
			exit(0);
	}

	printf("Connexion effectuee \n");

	/* Emission du message sur la socket */

	if (send(sock, message, strlen(message)+1, 0)==-1){
		perror("erreur send()");
		exit(0);
	}

	close(sock);

	printf("Bye!!!\n");


	return 0;

	}