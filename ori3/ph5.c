#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void task() {
    double x = 1.0 + 1.0;
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            task();
            exit(0);
        } else {
            wait(NULL);
        }
    }
    return 0;
}