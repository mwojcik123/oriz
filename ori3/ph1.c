#include <stdio.h>
#include <pthread.h>
#define endless 1

void* thread_function(void* unused) {
    (void)unused;
    while (endless) {
        putchar('o');
    }
    return NULL;
}

int main(void) {
    pthread_t tid;
    pthread_create(&tid, NULL, &thread_function, NULL);
    while (endless) {
        putchar('x');
    }
    return 0;
}