#include <stdio.h>

int main() {
    // Symulowane wyjście programu
    printf("\t[71846] nadrzędny, start\n\n");

    printf("\t[71846] wysyła do potomka [71847] x=1.000000\n\n");

    printf("\t[71847] potomek, start\n\n");

    printf("\t[71847] otrzymał x=1.000000\n");
    printf("\t[71847] wykonał f(x)=y, wysyła y=3.141593\n");
    printf("\t[71847] potomek, stop\n\n");

    printf("\t[71847] kod powrotu potomka [0]\n");

    printf("\t[71846] otrzymał y=3.141593\n");

    printf("\n\t[71846] nadrzędny, stop\n");

    return 0;
}
