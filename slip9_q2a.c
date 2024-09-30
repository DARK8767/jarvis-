//Bankers Algorithm for Several instances of single resource
#include <stdio.h>
#include <stdlib.h>

#define NUM_RESOURCES 3

int Allocation[NUM_RESOURCES][NUM_RESOURCES];
int Request[NUM_RESOURCES][NUM_RESOURCES];
int Available[NUM_RESOURCES];
int Max[NUM_RESOURCES][NUM_RESOURCES];
int Num_Processes;

void accept_resources() {
  printf("Enter the total available resources for each type:\n");
  for (int i = 0; i < NUM_RESOURCES; i++) {
    scanf("%d", &Available[i]);
  }
}

void accept_allocation() {
  printf("Enter the allocation matrix for each process:\n");
  for (int i = 0; i < Num_Processes; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      scanf("%d", &Allocation[i][j]);
    }
  }
}

void accept_request() {
  printf("Enter the request matrix for each process:\n");
  for (int i = 0; i < Num_Processes; i++) {
    for (int j = 0; j < NUM_RESOURCES; j++) {
      scanf("%d", &Request[i][j]);
    }
  }
}

void display_available() {
  printf("The available resources are: ");
  for (int i = 0; i < NUM_RESOURCES; i++) {
    printf("%d ", Available[i]);
  }
  printf("\n");
}

void is_safe() {
  int Finish[Num_Processes];  // Change NUM_RESOURCES to Num_Processes
  int Work[NUM_RESOURCES];
  int i;  // Define i before using in the loop

  // Initialize Finish and Work
  for (i = 0; i < Num_Processes; i++) {
    Finish[i] = 0;
    Work[i] = Available[i];
  }

  // Find a process that is not finished and has all of its resources
  while (1) {
    int found = 0;
    for (i = 0; i < Num_Processes; i++) {
      if (!Finish[i]) {
        found = 1;
        for (int j = 0; j < NUM_RESOURCES; j++) {
          if (Request[i][j] > Work[j]) {
            found = 0;
            break;  // Add a break statement here
          }
        }
      }
      if (found) {
        break;  // Increment i after finding a process
      }
    }

    // If no process is found, then the system is in a safe state
    if (!found) {
      printf("The system is in a safe state.\n");
      return;
    }

    // Allocate resources to the process and mark it as finished
    for (int j = 0; j < NUM_RESOURCES; j++) {
      Work[j] += Allocation[i][j];
    }
    Finish[i] = 1;
  }
}

int main() {
  printf("------ BANKERS ALGORITHM ------.\n");

  // Accept the number of processes
  printf("Enter the number of processes: ");
  scanf("%d", &Num_Processes);

  // Accept the total available resources
  accept_resources();

  // Accept the allocation matrix
  accept_allocation();

  // Accept the request matrix
  accept_request();

  // Display the available resources
  display_available();

  // Check for deadlock
  is_safe();

  return 0;
}
