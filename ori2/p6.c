#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main(void) {
    int pid, status;
    int one[2], two[2];
    double x = 1.0, y = 1.0;

    // Tworzymy potoki
    printf("\t[%d] nadrzędny, start\n\n", (int)getpid());

    if (pipe(one) < 0 || pipe(two) < 0) {
        printf("<!> błąd otwarcia łączy\n");
        exit(1);
    }

    // Tworzymy proces potomny
    switch (pid = (int)fork()) {
        case -1: // Błąd przy forkowaniu
            perror("<!> błąd inicjacji potomka");
            exit(1);

        case 0: // Kod wykonywany przez proces potomny
            printf("\t[%d] potomek, start\n\n", (int)getpid());

            close(one[1]); // Zamykamy niepotrzebne strony potoku
            close(two[0]);

            // Odczytujemy dane od procesu nadrzędnego
            read(one[0], (void*)&x, sizeof(double));
            printf("\t[%d] otrzymał x=%f\n", (int)getpid(), x);

            // Przetwarzamy dane
            y = x * M_PI;
            printf("\t[%d] wykonał f(x)=y, wysyła y=%f\n", (int)getpid(), y);

            // Wysyłamy wynik do procesu nadrzędnego
            write(two[1], (void*)&y, sizeof(double));
            printf("\t[%d] potomek, stop\n\n", (int)getpid());

            exit(0);

        default: // Kod wykonywany przez proces nadrzędny
            close(one[0]); // Zamykamy niepotrzebne strony potoku
            close(two[1]);

            // Wysyłamy dane do procesu potomnego
            printf("\t[%d] wysyła do potomka [%d] x=%f\n\n", (int)getpid(), pid, x);
            write(one[1], (void*)&x, sizeof(double));

            // Odbieramy wynik z procesu potomnego
            read(two[0], (void*)&y, sizeof(double));

            // Czekamy na zakończenie procesu potomnego
            wait(&status);

            // Wyświetlamy wynik
            printf("\t[%d] kod powrotu potomka [%d]\n", pid, status);
            printf("\t[%d] otrzymał y=%f\n", (int)getpid(), y);
            printf("\n\t[%d] nadrzędny, stop\n", (int)getpid());
    }

    return 0;
}
