#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        printf("Parent process\n");
        sleep(5);
        printf("Parent process exiting\n");
    } else if (pid == 0) {
        printf("Child process\n");
        printf("Parent process ID: %d\n", getppid());
        sleep(10);
        printf("Child process exiting\n");
    } else {
        printf("Fork failed\n");
        return 1;
    }

    return 0;
}
