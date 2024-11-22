#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fd[2];
    int pid, status;
    FILE* stream;

    // Tworzymy potok
    if (pipe(fd) < 0) {
        printf("błąd: nie udało się otworzyć łącza\n");
        exit(1);
    }

    // Tworzymy proces potomny
    pid = fork();
    if (pid == -1) { // Błąd przy forku
        perror("błąd: inicjalizacja procesu potomnego");
        exit(1);
    }

    if (pid == 0) { // Kod wykonywany przez proces potomny
        printf("<!>\tpotomek [%d] startuje\n", getpid());

        // Zamykamy deskryptor zapisu w potoku
        close(fd[1]);
        
        // Przekierowujemy stdin do potoku
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        // Wykonujemy sortowanie
        printf("------------------------------------------\n");
        execl("/usr/bin/sort", "sort", "--reverse", (char*)NULL);
        perror("execl failed"); // Jeśli execl się nie powiedzie
        exit(1);
    } else { // Kod wykonywany przez proces nadrzędny
        // Zamykamy deskryptor odczytu w potoku
        close(fd[0]);

        // Otwarcie deskryptora zapisu
        stream = fdopen(fd[1], "w");

        // Zapisujemy dane do potoku
        fprintf(stream, "\tAaaaa\n");
        fprintf(stream, "\tBbbbb\n");
        fprintf(stream, "\tCcccc\n");
        fprintf(stream, "\tDdddd\n");
        fflush(stream); // Wymuszamy zapis do potoku
        close(fd[1]); // Zamykamy deskryptor zapisu

        // Czekamy na zakończenie procesu potomnego
        wait(&status);

        // Wyświetlamy wynik zakończenia procesu potomnego
        printf("------------------------------------------\n");
        printf("<!>\tpotomek [%d] zakończył działanie i zwrócił [%d]\n", pid, status);
    }

    return 0;
}
