#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* hello(void* n) {
    printf("jestem wątkiem #%ld\n", (long)n);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("użycie: %s <liczba_wątków>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    pthread_t threads[n];

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, hello, (void*)(long)(i + 1));
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}