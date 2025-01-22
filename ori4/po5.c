#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SHARE 1 // współdzielenie semafora między procesami (true)

sem_t id; // identyfikator używanego semafora
int n;    // zmienna globalna, na której działają wątki

void* thread(void *ptr) {
    int i = *((int *)ptr); // pobranie numeru kolejnego wątku
    printf("wątek %d: start\n", i);

    sem_wait(&id); // wątek wykonuje P() (wyłączność)
    printf("wątek %d: krytyczna, start\n", i);
    printf("wątek %d: n = %d\n", i, n);
    printf("wątek %d: n++\n", i);
    n++;
    printf("wątek %d: n = %d\n", i, n);
    printf("wątek %d: krytyczna, stop\n", i);

    sem_post(&id); // wątek wykonuje V() (zwolnienie)
    printf("wątek %d: stop\n", i);

    pthread_exit(0);
}

int main(int argc, char **argv) {
    int i[] = {1, 2}; // tablica numerów wątków
    pthread_t first, second;

    // tworzenie semafora (POSIX, nienazwany)
    sem_init(&id, !SHARE, 1);

    // uruchamianie wątków
    pthread_create(&first, NULL, thread, (void *)(i + 0));
    pthread_create(&second, NULL, thread, (void *)(i + 1));

    /* tutaj pracują wątki */
    pthread_join(first, NULL);
    pthread_join(second, NULL);

    // wątki zakończyły działanie, usuwanie semafora
    sem_destroy(&id);

    return 0;
}
