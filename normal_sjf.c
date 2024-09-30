#include <stdio.h>
#include <stdlib.h>

// Process structure
struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform Shortest Job First scheduling
void sjf_scheduling(struct Process *processes, int n) {
    // Sort processes based on burst time using Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    // Allocate the first position to the process arrived at time 0
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time > currentTime) {
            currentTime = processes[i].arrival_time;
            break;
        }
    }

    // Calculate turnaround time and waiting time
    int *turnaround_time = (int *)malloc(n * sizeof(int));
    int *waiting_time = (int *)malloc(n * sizeof(int));
    turnaround_time[0] = processes[0].burst_time;
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        currentTime += processes[i - 1].burst_time;
        turnaround_time[i] = currentTime + processes[i].burst_time - processes[i].arrival_time;
        waiting_time[i] = turnaround_time[i] - processes[i].burst_time;
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].process_id);
    }
    printf("|\n");

    // Print process details
    printf("\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, turnaround_time[i], waiting_time[i]);
    }

    // Calculate average turnaround time and average waiting time
    float avg_turnaround_time = 0, avg_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        avg_turnaround_time += turnaround_time[i];
        avg_waiting_time += waiting_time[i];
    }

    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    // Print average turnaround time and average waiting time
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);

    // Free dynamically allocated memory
    free(turnaround_time);
    free(waiting_time);
}

int main() {
    int n;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Allocate memory for an array of processes
    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));

    // Get process details from the user
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].process_id = i + 1;
    }

    // Perform Shortest Job First scheduling
    sjf_scheduling(processes, n);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
