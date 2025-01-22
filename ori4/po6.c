#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex; // mutex do synchronizacji
pthread_cond_t cond;   // zmienna warunkowa

unsigned long int n = 0;             // monitorowana zmienna
const unsigned long int no = 10;     // pożądana wartość

void* watch(void *arg) {
    printf("[%lu] watch(): start\n", (unsigned long)pthread_self());

    pthread_mutex_lock(&mutex);
    while (n < no) { // czekanie na spełnienie warunku
        pthread_cond_wait(&cond, &mutex);
    }
    printf("[%lu] watch(): V() %lu\n", (unsigned long)pthread_self(), n);
    pthread_mutex_unlock(&mutex);

    printf("[%lu] watch(): stop\n", (unsigned long)pthread_self());
    pthread_exit(NULL);
}

void* worker(void *arg) {
    for (n = 0; n < 25; n++) {
        printf("[%lu] worker(): %lu\n", (unsigned long)pthread_self(), n);

        if (!(n - no)) { // gdy n osiągnie wartość `no`
            pthread_cond_broadcast(&cond);
            break;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    pthread_t tid[2];

    // inicjalizacja mutexa i zmiennej warunkowej
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // tworzenie wątków
    pthread_create(&tid[0], NULL, worker, NULL);
    pthread_create(&tid[1], NULL, watch, NULL);

    // oczekiwanie na zakończenie wątków
    pthread_join(tid[1], NULL);
    pthread_join(tid[0], NULL);

    // usuwanie mutexa i zmiennej warunkowej
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("[%lu] main(): stop\n", (unsigned long)pthread_self());
    return 0;
}
