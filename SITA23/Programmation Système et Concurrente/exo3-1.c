#define _REENTRANT

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int _n1, _n2;

sem_t sem1, sem2;

void *foncThread1 (void *a) {
	a = a ;
	_n1=1;
    sem_post(&sem1);
	return 0;
}

void *foncThread2 (void *a) {
	a = a ;
	_n2=2;
    sem_post(&sem2);
	return 0;
}

void *foncThread3 (void *a) {
	a = a ;
    sem_wait(&sem1);
    sem_wait(&sem2);
	int n3 =_n1+_n2;
	printf("n3 = %d\n", n3);
	return 0;
}
int main(void) {

	sem_init( &sem1, 0, 0);
	sem_init( &sem2, 0, 0);

	pthread_t idThread1, idThread2, idThread3 ;
	
	pthread_create(&idThread1, NULL, foncThread1, NULL);
	pthread_create(&idThread2, NULL, foncThread2, NULL);
	pthread_create(&idThread3, NULL, foncThread3, NULL);
	
	pthread_join(idThread1, NULL);
	pthread_join(idThread2, NULL);
	pthread_join(idThread3, NULL);

}
