#include <stdio.h>

int main() {
    // symulowane dane
    char name[] = "km";
    int counter = 7;

    // symulowany wynik działania programu
    printf("*** otwarto semafor\t%s\n", name);
    printf(" licznik semafora\t%d\n", counter);
    printf("*** zamknięto semafor\t%s\n", name);
    printf("*** usunięto semafor\t%s\n", name);

    return 0;
}
