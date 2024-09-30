#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main() {
  int pid;

  pid = fork();

  if (pid == 0) {
    // Child process
    printf("Child process ID: %d\n", getpid());
    printf("Child process nice value: %d\n", nice(10));

    // Simulate some work
    for (int i = 0; i < 10000000; i++) {
      // Do nothing
    }

    printf("Child process exiting\n");
    exit(0);
  } else {
    // Parent process
    printf("Parent process ID: %d\n", getpid());
    printf("Parent process nice value: %d\n", nice(-10));

    // Simulate some work
    for (int i = 0; i < 10000000; i++) {
      // Do nothing
    }

    wait(NULL);
    printf("Parent process exiting\n");
    exit(0);
  }

  return 0;
}

