#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// konieczna deklaracja mutexa
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int N = 0;

void *thread(void *arg) {
    int n;
    int i;

    for (i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex); // zgłoszenie
        n = N;
        n++;
        printf("thread() [%lu]\n", (unsigned long)pthread_self());
        fflush(stdout);
        sleep(1); // symulacja opóźnienia
        N = n;
        pthread_mutex_unlock(&mutex); // zwolnienie
    }

    pthread_exit(NULL);
}

int main(void) {
    pthread_t tid;
    int i;

    // tworzenie wątku
    if (pthread_create(&tid, NULL, thread, NULL)) {
        perror("...pthread_create()...");
        exit(1);
    }

    for (i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        N--; // dekrementacja wątku głównego
        printf("main() [%lu]\n", (unsigned long)pthread_self());
        fflush(stdout);
        sleep(1); // symulacja opóźnienia
        pthread_mutex_unlock(&mutex);
    }

    // oczekiwanie na zakończenie wątku
    if (pthread_join(tid, NULL)) {
        perror("...pthread_join()...");
        exit(2);
    }

    // niszczenie mutexa
    if (pthread_mutex_destroy(&mutex)) {
        perror("...pthread_mutex_destroy()...");
        exit(3);
    }

    printf("\nglobalnie N=%d, po wykonaniu 5+5 iteracji\n", N);
    return 0;
}
