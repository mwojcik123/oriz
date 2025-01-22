#include <stdio.h>

int main() {
    // początkowa wartość zmiennej globalnej
    int N = 0;
    int i;

    // symulacja działania wątku głównego i wątku potomnego
    for (i = 0; i < 5; i++) {
        // wątek główny
        printf("main() [1]\n");
        N--; // dekrementacja

        // wątek potomny
        printf("thread() [2]\n");
        N++; // inkrementacja
    }

    // końcowy wynik
    printf("\nglobalnie N=%d, po wykonaniu 5+5 iteracji\n", N);

    return 0;
}
