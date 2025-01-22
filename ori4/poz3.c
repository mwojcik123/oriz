#include <stdio.h>

int main() {
    int n = 5; // liczba wątków
    int N = 0; // suma liczb naturalnych
    int i;

    // symulacja działania wątków
    for (i = 1; i <= n; i++) {
        printf("thread() [id=%d]: dodaje %d do sumy\n", i, i);
        N += i;
    }

    // wyświetlenie wyniku
    printf("|\n| suma ciągu n = %d, liczb naturalnych wynosi n*(n+1)/2 = %d\n|\n", n, N);
    return 0;
}
