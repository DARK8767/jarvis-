#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process with PID: %d\n", getpid());
        sleep(5); // Simulate some work in the child process
        printf("Child process exiting\n");
    } else {
        // Parent process
        printf("Parent process with PID: %d\n", getpid());
        printf("Parent process exiting\n");
        // sleep(2); // Uncomment to see the effect of the parent terminating before the child
    }

    return 0;
}
