#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

// funkcja podcałkowa
double sine(double x) {
    return sin(2 * M_PI * x) * exp(-x);
}

// funkcja obliczająca wartość całki
double quad(unsigned int n, double a, double b, double (*fun)(double)) {
    unsigned int k;
    double xk, sum;
    sum = fun(a) + fun(b);

    for (k = 1; k < n; k++) {
        xk = a + (b - a) * k / n;
        sum += 2.0 * fun(xk);
    }
    return ((b - a) / (2.0 * n) * sum);
}

int main(void) {
    int pid, status;
    unsigned int n = 3200;
    double a = 0.0, b = 1.0, I = 0.0;
    int fd[2]; // deskryptory potoku

    // tworzenie potoku
    if (pipe(fd) < 0) {
        printf("błąd: nie udało się otworzyć łącza\n");
        exit(1);
    }

    switch (fork()) {
        case -1: // błąd przy tworzeniu procesu potomnego
            perror("błąd: inicjalizacja procesu potomnego nie powiodła się");
            exit(1);

        case 0: // proces potomny
            close(fd[0]); // zamykamy odczyt w potomku
            I = quad(n, a, b, sine);
            printf("[%d] wartość całki: %19.6f\n", getpid(), I);
            write(fd[1], (void*)&I, sizeof(double)); // przesyłamy wynik do procesu nadrzędnego
            close(fd[1]); // zamykamy zapis
            exit(0);

        default: // proces nadrzędny
            close(fd[1]); // zamykamy zapis w nadrzędnym
            read(fd[0], (void*)&I, sizeof(double)); // odczytujemy wynik od potomka
            close(fd[0]); // zamykamy odczyt
            wait(&status); // czekamy na zakończenie potomka
            printf("[%d] zakończył się z kodem %d\n", pid, status);
            printf("[%d] otrzymał wartość całki: %16.6f\n", getpid(), I);
    }

    return 0;
}
