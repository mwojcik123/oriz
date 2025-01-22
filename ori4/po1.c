#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int N = 0; // zmienna globalna, na której będą działać wątki

void *thread(void *arg) {
    int n, i;

    for (i = 0; i < 5; i++) {
        n = N; // pobranie wartości zmiennej globalnej
        n++;   // inkrementacja kopii lokalnej
        printf("thread() [%lu]\n", (unsigned long)pthread_self());
        fflush(stdout);
        sleep(1); // czekanie 1 sekundy
        N = n;    // zapisanie wartości do zmiennej globalnej
    }

    pthread_exit(NULL);
}

int main(void) {
    pthread_t tid;
    int i;

    // tworzenie wątku potomnego
    if (pthread_create(&tid, NULL, thread, NULL)) {
        perror("...pthread_create()...");
        exit(1);
    }

    // działanie wątku głównego
    for (i = 0; i < 5; i++) {
        N--; // dekrementacja zmiennej globalnej
        printf("main() [%lu]\n", (unsigned long)pthread_self());
        fflush(stdout);
        sleep(1); // czekanie 1 sekundy
    }

    // oczekiwanie na zakończenie wątku potomnego
    if (pthread_join(tid, NULL)) {
        perror("...pthread_join()...");
        exit(2);
    }

    // wyświetlenie końcowego wyniku
    printf("\nglobalnie N=%d, po wykonaniu 5+5 iteracji\n", N);
    return 0;
}
