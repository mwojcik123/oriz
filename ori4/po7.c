#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // tylko aby wywołać sleep()
#include <pthread.h>

pthread_barrier_t barrier; // zmienna identyfikująca barierę
unsigned count;            // licznik odwołań do bariery

void *thread(void *arg) {
    // tylko komunikat diagnostyczny
    printf("[%lu] thread wait signal...!\n", (unsigned long)pthread_self());
    pthread_barrier_wait(&barrier); // wait() względem bariery
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

        count = n + 1; // licznik bariery ustawiamy na n wątków + 1

        // alokacja pamięci na identyfikatory wątków
        if (!(tid = (pthread_t *)calloc((size_t)n, sizeof(pthread_t)))) {
            perror("...calloc()...");
            exit(2);
        }

        // inicjalizacja bariery
        pthread_barrier_init(&barrier, NULL, count);

        // tworzenie wątków
        for (i = 0; i < n; i++) {
            if (pthread_create((tid + i), NULL, thread, NULL)) {
                free((void *)tid);
                perror("...pthread_create()...");
                exit(2);
            }
        }

        // wątek główny (n + 1)
        printf("[%lu] main()...?\n", (unsigned long)pthread_self());
        sleep(1);
        pthread_barrier_wait(&barrier); // teraz dopiero będzie zwolniona
        printf("[%lu] main()...done\n", (unsigned long)pthread_self());

        // dołączanie wątków
        for (i = 0; i < n; i++) {
            if (pthread_join(*(tid + i), NULL)) {
                free((void *)tid);
                perror("...pthread_join()...");
                exit(2);
            }
        }

        // końcowe porządki
        free((void *)tid);
        if (pthread_barrier_destroy(&barrier)) {
            perror("...pthread_barrier_destroy()...");
            exit(2);
        }
    } else {
        printf("...wywołanie programu %s <ilość wątków>\n", argv[0]);
        exit(1);
    }

    return 0;
}
