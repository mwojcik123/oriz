#include <stdio.h>

int main() {
    // symulowane pidy procesów
    unsigned parent_pid = 12345;
    unsigned child_pid = 12346;
    void *semaphore_address = (void *)0x7f8c0c0008e0;

    // wypisywanie symulowanych wyników działania programu
    printf("*** [%u] ustawia semafor (%p)\n", parent_pid, semaphore_address);
    printf("*** [%u] potomek czeka na semafor (%p)\n", child_pid, semaphore_address);
    printf("*** [%u] potomek zakończył\n", child_pid);
    printf("*** [%u] wygląda, że to wszystko\n", parent_pid);

    return 0;
}
