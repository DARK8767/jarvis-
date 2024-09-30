// Program for FCFS Scheduling algorithm
#include <stdio.h>
#include <stdlib.h>

// Function to generate a random number between min and max
int generateRandomBurst(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to calculate turnaround time and waiting time
void calculateTimes(int n, int arrival[], int burst[], int turnaround[], int waiting[]) {
    waiting[0] = 0;
    turnaround[0] = burst[0];

    for (int i = 1; i < n; i++) {
        waiting[i] = turnaround[i - 1];
        turnaround[i] = waiting[i] + burst[i];
    }
}

// Function to display Gantt chart and times
void displayOutput(int n, int arrival[], int burst[], int turnaround[], int waiting[]) {
    printf("\nGantt Chart:\n");

    // Display the Gantt chart
    for (int i = 0; i < n; i++) {
        printf("  P%d  ", i);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("|-----");
    }
    printf("|\n");

    for (int i = 0; i < n; i++) {
        printf("  %d   ", turnaround[i]);
    }
    printf("\n\n");

    // Display turnaround and waiting times
    printf("Process\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", i, turnaround[i], waiting[i]);
    }

    // Calculate and display average times
    float avgTurnaround = 0, avgWaiting = 0;
    for (int i = 0; i < n; i++) {
        avgTurnaround += turnaround[i];
        avgWaiting += waiting[i];
    }

    avgTurnaround /= n;
    avgWaiting /= n;

    printf("\nAverage Turnaround Time: %.2f", avgTurnaround);
    printf("\nAverage Waiting Time: %.2f\n", avgWaiting);
}

int main() {
    int n;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], turnaround[n], waiting[n];

    // Get arrival time and first CPU burst for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i);
        scanf("%d", &arrival[i]);

        printf("Enter burst time for process P%d: ", i);
        scanf("%d", &burst[i]);
    }

    // Set fixed I/O waiting time
    int ioWaiting = 2;

    // Calculate the turnaround time and waiting time
    calculateTimes(n, arrival, burst, turnaround, waiting);

    // Display the Gantt chart and times
    displayOutput(n, arrival, burst, turnaround, waiting);

    return 0;
}
