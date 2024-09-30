#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    else if (pid == 0) {
        printf("Child Process ID: %d\n", getpid());
        printf("Hello World\n");
    }
    else {
        printf("Parent Process ID: %d\n", getpid());
        printf("Hi\n");
    }

    return 0;
}
