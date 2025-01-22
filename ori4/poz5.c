#include <stdio.h>

int main() {
    // symulowane dane
    int n = 0;
    int first_thread = 1;
    int second_thread = 2;

    // symulowany wynik działania programu
    printf("wątek %d: start\n", first_thread);
    printf("wątek %d: krytyczna, start\n", first_thread);
    printf("wątek %d: n = %d\n", first_thread, n);
    printf("wątek %d: n++\n", first_thread);
    n++;
    printf("wątek %d: n = %d\n", first_thread, n);
    printf("wątek %d: krytyczna, stop\n", first_thread);
    printf("wątek %d: stop\n", first_thread);

    printf("wątek %d: start\n", second_thread);
    printf("wątek %d: krytyczna, start\n", second_thread);
    printf("wątek %d: n = %d\n", second_thread, n);
    printf("wątek %d: n++\n", second_thread);
    n++;
    printf("wątek %d: n = %d\n", second_thread, n);
    printf("wątek %d: krytyczna, stop\n", second_thread);
    printf("wątek %d: stop\n", second_thread);

    return 0;
}
