#include <stdio.h>
#include <unistd.h>

int main() {
    int n = 3; // liczba wątków
    printf("[1] main()...?\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] thread wait signal...!\n", i + 2);
    }
    sleep(1);
    printf("[1] main()...done\n");
    return 0;
}
