
#define _REENTRANT

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *foncThread (void *a) {
	long  num = (long)a;
	unsigned int i;
	char ch[10];

	// Creation d'une chaine de caracteres contenant le numero du thread
	sprintf(ch, "Th%ld\n", num);

	//affichage caractere par caractere de cette chaine, atente d'1 seconde entre chaque caractere
    pthread_mutex_lock(&mutex);
	for (i=0; i<strlen(ch); i++) {
		printf("%c", ch[i]);
	}
    pthread_mutex_unlock(&mutex);
	
	return 0;
}


int main(void) {
	
	long i;
	pthread_t idThread[5] ;
	
	// boucle de creation de 5 threads : on passe le numero du thread en parametre
	for (i=0; i<5; i++)
		pthread_create(&idThread[i], NULL, foncThread, (void *)i);
	
	// boucle d'attente de la terminaison des 5 threads
	for (i=0; i<5; i++)	
		pthread_join(idThread[i], NULL);
	
	return 0;
}
