// Non-Preemptive Priority
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int turnaround_time;
    int waiting_time;
} Process;

void swap(Process *xp, Process *yp) {
    Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortProcessesByPriority(Process processes[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (processes[j].priority > processes[j+1].priority)
                swap(&processes[j], &processes[j+1]);
}

void calculateTurnaroundTime(Process processes[], int n) {
    processes[0].turnaround_time = processes[0].burst_time;
    for (int i = 1; i < n; i++) {
        processes[i].turnaround_time = processes[i-1].turnaround_time + processes[i].burst_time;
    }
}

void calculateWaitingTime(Process processes[], int n) {
    processes[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i-1].turnaround_time;
    }
}

void printGanttChart(Process processes[], int n) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].pid);
    }
    printf("|\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process P%d: ", processes[i].pid);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }

    sortProcessesByPriority(processes, n);

    // Simulating fixed I/O waiting time (2 units)
    for (int i = 0; i < n; i++) {
        processes[i].burst_time += 2;
    }

    calculateTurnaroundTime(processes, n);
    calculateWaitingTime(processes, n);

    printGanttChart(processes, n);

    printf("\nProcess\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].pid, processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Calculate average turnaround time and waiting time
    float avg_turnaround_time = 0, avg_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);

    return 0;
}
