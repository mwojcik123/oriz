#include <stdio.h>

int main() {
    printf("PID[1638] tworzy wątek,...#1...\n");
    printf("PID[1638] tworzy wątek,...#2...\n");
    printf("PID[1638] tworzy wątek,...#3...\n");
    printf("PID[1638] ...jestem wątkiem #3! TID[-413075712]\n");
    printf("PID[1638] ...jestem wątkiem #2! TID[-404683008]\n");
    printf("PID[1638] ...jestem wątkiem #1! TID[-396290304]\n");

    return 0;
}