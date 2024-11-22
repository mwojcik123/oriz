#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

int main() {
    int lacze[2], ilosc_bajtow;
    char bufor[PIPE_BUF];

    // tworzenie potoku
    if (pipe(lacze) < 0) {
        printf("błąd: nie udało się otworzyć łącza\n");
        exit(1);
    }

    // forkujemy proces
    switch (fork()) {
        case -1: // błąd forka
            perror("błąd: inicjalizacja procesu potomnego nie powiodła się");
            exit(1);

        case 0: // kod potomka
            close(lacze[0]); // zamykamy odczyt
            write(lacze[1], "\n\t[wiadomość od potomka]\n\n", 29);
            close(lacze[1]); // zamykamy zapis
            exit(0);

        default: // kod procesu nadrzędnego
            close(lacze[1]); // zamykamy zapis
            ilosc_bajtow = read(lacze[0], (void *)bufor, PIPE_BUF);
            close(lacze[0]); // zamykamy odczyt
            write(STDOUT_FILENO, bufor, ilosc_bajtow);
    }

    return 0;
}