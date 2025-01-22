#include <stdio.h>

int main() {
    unsigned long int n = 1000; // rozmiar tablicy
    unsigned long int m = 4;   // liczba wątków
    double sum = 0.0;

    // obliczenie sumy
    for (unsigned long int i = 1; i <= n; i++) {
        sum += i;
    }

    // wyświetlenie wyniku
    printf("|\n| suma elementów tablicy X wynosi %f\n|\n", sum);

    return 0;
}
