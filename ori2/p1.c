#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

// funkcja obliczająca wartość całki
double calculate_integral(unsigned int nodes, double lower_bound, double upper_bound, double (*function)(double)) {
    unsigned int i;
    double x, result;
    result = function(lower_bound) + function(upper_bound);

    for (i = 1; i < nodes; i++) {
        x = lower_bound + (upper_bound - lower_bound) * i / nodes;
        result += 2.0 * function(x);
    }
    return ((upper_bound - lower_bound) / (2.0 * nodes) * result);
}

// funkcja podcałkowa
double function_to_integrate(double x) {
    return sin(2 * M_PI * x) * exp(-x);
}

int main() {
    unsigned int node_count = 3200;
    double start = 0.0, end = 1.0, integral_result = 0.0;
    int process_id, child_status;

    // tworzenie procesu potomnego
    switch (fork()) {
        case -1: // błąd podczas tworzenia procesu
            perror("error: failed to create child process");
            exit(1);

        case 0: // kod wykonywany przez proces potomny
            integral_result = calculate_integral(node_count, start, end, function_to_integrate);
            printf("[%d] calculated integral value: %16.6f\n", getpid(), integral_result);
            exit(0);

        default: // kod wykonywany przez proces nadrzędny
            printf("[%d] doing other important tasks...\n", getpid());
            process_id = wait(&child_status);
            printf("[%d] finished with exit code %d\n", process_id, child_status);
            printf("[%d] final integral value: %16.6f\n", getpid(), integral_result);
    }

    return 0;
}
