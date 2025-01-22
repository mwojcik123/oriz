#include <stdio.h>

int main() {
    printf("[1] konsument: czeka...\n");
    printf("[2] producent: ???\n");
    sleep(1); // symulacja opóźnienia
    printf("[1] konsument: kontynuacja\n");
    return 0;
}
