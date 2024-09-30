#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t parent_pid, child_pid;

    parent_pid = getpid(); // Get the parent process ID

    child_pid = fork(); // Create a child process

    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Child process
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());

        // Replace the child process image with a new program using exec()
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);

        // If execvp() fails, it will continue from here
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), child_pid);

        // Wait for the child process to complete
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit normally\n");
        }

        printf("Parent process continues after child process termination\n");
    }

    return 0;
}
