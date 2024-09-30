// Banker's algorithm (Slip4)
#include <stdio.h>

// Number of processes and resources
#define P 5
#define R 4

// Function to calculate the need matrix
void calculateNeedMatrix(int need[P][R], int max[P][R], int allocation[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
int isSafe(int processes[], int available[], int max[][R], int allocation[][R]) {
    int need[P][R];
    calculateNeedMatrix(need, max, allocation);

    int finish[P] = {0}; // Array to track finished processes
    int safeSeq[P]; // Array to store the safe sequence
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < P) {
        int found = 0;
        for (int p = 0; p < P; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is not in safe state!\n");
            return 0;
        }
    }

    // If the system is in a safe state, display the safe sequence
    printf("System is in safe state. Safe sequence: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    return 1;
}

// Function to check if a request can be granted immediately
int canGrantRequest(int process, int request[], int available[], int max[][R], int allocation[][R]) {
    int need[R];
    for (int i = 0; i < R; i++) {
        need[i] = max[process][i] - allocation[process][i];
    }

    for (int i = 0; i < R; i++) {
        if (request[i] > need[i] || request[i] > available[i]) {
            return 0; // Request cannot be granted
        }
    }

    return 1; // Request can be granted
}

int main() {
    // Initialize available resources
    int available[R] = {1, 5, 2, 0};

    // Initialize maximum resources for each process
    int max[P][R] = {
        {0, 0, 1, 2},
        {1, 7, 5, 0},
        {2, 3, 5, 6},
        {0, 6, 5, 2},
        {0, 6, 5, 6}
    };

    // Initialize allocated resources for each process
    int allocation[P][R] = {
        {0, 0, 1, 2},
        {1, 0, 0, 0},
        {1, 3, 5, 4},
        {0, 6, 3, 2},
        {0, 0, 1, 4}
    };

    // a) Calculate and display the content of the need matrix
    int need[P][R];
    calculateNeedMatrix(need, max, allocation);
    printf("Need Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // b) Is the system in a safe state? If yes, display the safe sequence
    if (isSafe(NULL, available, max, allocation)) {
        // c) If a request from process P arrives for (0, 4, 2, 0), can it be granted immediately?
        int processP = 1;
        int request[R] = {0, 4, 2, 0};
        if (canGrantRequest(processP, request, available, max, allocation)) {
            // Grant the request
            for (int i = 0; i < R; i++) {
                available[i] -= request[i];
                allocation[processP][i] += request[i];
                need[processP][i] -= request[i];
            }

            // Check if the system is still in a safe state after the request
            if (isSafe(NULL, available, max, allocation)) {
                printf("Request granted. System is still in safe state.\n");
            } else {
                // Rollback the changes if the system is not in a safe state
                printf("Request cannot be granted. Rolling back changes.\n");
                for (int i = 0; i < R; i++) {
                    available[i] += request[i];
                    allocation[processP][i] -= request[i];
                    need[processP][i] += request[i];
                }
            }
        } else {
            printf("Request cannot be granted immediately.\n");
        }
    }

    return 0;
}
