#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortProcesses(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void calculateTimes(Process processes[], int n) {
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].turnaround_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void printGanttChart(Process processes[], int n) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].process_id);
    }
    printf("|\n");
}

int main() {
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes. Exiting...\n");
        return 1;
    }

    Process processes[MAX_PROCESSES];

    for (i = 0; i < n; i++) {
        processes[i].process_id = i + 1;

        printf("Enter arrival time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);

        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);

        // Assuming fixed I/O waiting time of 2 units
        processes[i].burst_time += 2;

        // Generate next CPU burst using random function
        processes[i].burst_time += rand() % 10;
    }

    // Sort processes based on burst time
    sortProcesses(processes, n);

    // Calculate waiting time and turnaround time
    calculateTimes(processes, n);

    // Print Gantt Chart
    printGanttChart(processes, n);

    // Print Turnaround Time and Waiting Time
    printf("\nProcess\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].process_id, processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Calculate and print average times
    float avg_turnaround_time = 0, avg_waiting_time = 0;
    for (i = 0; i < n; i++) {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);

    return 0;
}
