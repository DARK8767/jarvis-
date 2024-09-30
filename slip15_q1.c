#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child process ID: %d\n", getpid());
        
        // Use execl() to execute the "ls" command
        execl("/bin/ls", "ls", (char *)NULL);  

        // If execl() fails
        perror("execl failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process ID: %d\n", getpid());
        
        // Parent goes to sleep
        printf("Parent is going to sleep for 5 seconds...\n");
        sleep(5);

        // Wait for the child to complete
        wait(NULL);

        printf("Parent process exiting.\n");
    }

    return 0;
}
