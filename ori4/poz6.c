#include <stdio.h>

int main() {
    unsigned long int n = 0;             // monitorowana zmienna
    const unsigned long int no = 10;     // pożądana wartość

    printf("[1] watch(): start\n");

    for (n = 0; n < 25; n++) {
        printf("[2] worker(): %lu\n", n);

        if (n == no) { // gdy n osiągnie wartość `no`
            printf("[1] watch(): V() %lu\n", n);
            break;
        }
    }

    printf("[1] watch(): stop\n");
    printf("[3] main(): stop\n");

    return 0;
}
