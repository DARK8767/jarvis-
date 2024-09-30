#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int nice_value;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        nice_value = nice(10);
        printf("Child process with PID %d has a nice value of %d\n", getpid(), nice_value);
    } else {
        // Parent process
        nice_value = nice(0);
        printf("Parent process with PID %d has a nice value of %d\n", getpid(), nice_value);
    }

    return 0;
}
