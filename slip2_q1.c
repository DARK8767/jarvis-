#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t child_pid;
    
    // Fork a child process
    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // This is the child process
        printf("Child Process (PID: %d): Hello World\n", getpid());
    } else {
        // This is the parent process
        printf("Parent Process (PID: %d): Hi\n", getpid());
    }

    return 0;
}

