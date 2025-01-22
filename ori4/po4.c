#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>

int main(int argc, char **argv) {
    sem_t *id;
    pid_t child;
    int status;

    // otwarcie lub utworzenie semafora
    id = sem_open("szlaban", O_CREAT, S_IRUSR | S_IWUSR, 0);

    // tworzenie procesu potomnego
    switch ((int)(child = fork())) {
        case -1: // błąd podczas forka
            perror("...fork()...");
            exit(1);
            break;

        case 0: // kod dla procesu potomnego
            printf("*** [%u] potomek czeka na semafor (%p)\n", 
                   (unsigned)getpid(), id);
            sem_wait(id);
            printf("*** [%u] potomek zakończył\n", (unsigned)getpid());
            exit(0);

        default: // kod dla procesu nadrzędnego
            printf("*** [%u] ustawia semafor (%p)\n", 
                   (unsigned)getpid(), id);
            sem_post(id);

            if (!wait(&status)) { // czekanie na zakończenie procesu potomnego
                perror("... wait()...");
                exit(2);
            } else {
                printf("*** [%u] wygląda, że to wszystko\n", 
                       (unsigned)getpid());
                sem_close(id);        // zamknięcie semafora
                sem_unlink("szlaban"); // usunięcie semafora
            }
    }

    return 0;
}
