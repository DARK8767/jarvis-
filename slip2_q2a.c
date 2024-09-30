//Program for SJF Non Preemptive
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
} Process;

int compare_arrival_time(const void *a, const void *b) {
    return ((Process *)a)->arrival_time - ((Process *)b)->arrival_time;
}

int compare_burst_time(const void *a, const void *b) {
    return ((Process *)a)->burst_time - ((Process *)b)->burst_time;
}

void simulate_sjf(Process *processes, int n) {
    int current_time = 0;

    // Sort the processes based on their arrival time
    qsort(processes, n, sizeof(Process), compare_arrival_time);

    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        // Simulate fixed I/O waiting time (2 units)
        current_time += 2;

        // Sort the available processes based on burst time
        int remaining = n - i;
        Process *available = &processes[i];
        qsort(available, remaining, sizeof(Process), compare_burst_time);

        Process *current = &available[0];
        current->waiting_time = current_time - current->arrival_time;
        current->turnaround_time = current->waiting_time + current->burst_time;

        printf("| P%d ", current->process_id);
        current_time += current->burst_time;
    }
    printf("|\n");

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }

    float avg_waiting_time = 0.0;
    float avg_turnaround_time = 0.0;

    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    srand(time(NULL));

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = malloc(n * sizeof(Process));

    printf("Enter arrival time and initial burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    simulate_sjf(processes, n);

    free(processes);
    return 0;
}

