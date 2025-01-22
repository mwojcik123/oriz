#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // mutex do synchronizacji
int N = 0; // zmienna globalna przechowująca sumę

void *thread(void *arg) { // funkcja wątku
    int id = *((int *)arg);

    pthread_mutex_lock(&mutex); // P() aby zapewnić wątkowi wyłączność
    N += id; // odwołanie do zmiennej globalnej
    pthread_mutex_unlock(&mutex); // V() zwolnienie
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    pthread_t *tid;
    int i, n;

    if (argc > 1) {
        sscanf(argv[1], "%d", &n);

        if (n < 2) {
            printf("...n<2, przyjęto n=2...\n");
            n = 2;
        }

        // tworzenie tablicy identyfikatorów wątków
        if (!(tid = (pthread_t *)calloc((size_t)n, sizeof(pthread_t)))) {
            perror("...calloc()...");
            exit(2);
        }

        // uruchamianie wątków
        for (i = 0; i < n; i++) {
            int *id = malloc(sizeof(int)); // alokacja pamięci dla identyfikatora
            *id = i + 1;
            if (pthread_create((tid + i), NULL, thread, (void *)id)) {
                free((void *)tid);
                perror("...pthread_create()...");
                exit(2);
            }
        }

        // dołączanie wątków
        for (i = 0; i < n; i++) {
            if (pthread_join(*(tid + i), NULL)) {
                free((void *)tid);
                perror("...pthread_join()...");
                exit(2);
            }
        }

        free((void *)tid); // zwalnianie pamięci

        if (pthread_mutex_destroy(&mutex)) {
            perror("...pthread_mutex_destroy()...");
            exit(2);
        }

        printf("|\n| suma ciągu n = %d, liczb naturalnych wynosi n*(n+1)/2 = %d\n|\n", n, N);
    } else {
        // wywołanie programu jest niepoprawne
        printf("...wywołanie programu %s <ilość wątków>\n", argv[0]);
        exit(1);
    }

    return 0;
}
