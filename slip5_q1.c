#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        printf("Parent process (PID: %d) with default priority.\n", getpid());
        printf("Parent process nice value: %d\n", nice(0));
    } else {
        // Child process
        printf("Child process (PID: %d) with default priority.\n", getpid());
        printf("Child process nice value before adjustment: %d\n", nice(0));

        // Adjust the nice value to assign higher priority
        int new_priority = nice(10);
        if (new_priority == -1) {
            perror("Nice adjustment failed");
            exit(EXIT_FAILURE);
        }

        printf("Child process nice value after adjustment: %d\n", new_priority);
    }

    return 0;
}
