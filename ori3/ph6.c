#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* task(void* arg) {
    double x = 1.0 + 1.0;
    return NULL;
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);
    pthread_t threads[n];
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, task, NULL);
    }
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}