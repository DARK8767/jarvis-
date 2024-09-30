#include <stdio.h>
#include <stdlib.h>

// Process structure to store process details
struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
};

// Function to perform FCFS scheduling
void FCFS(struct Process *processes, int n) {
    int completionTime[n], turnaroundTime[n], waitingTime[n];

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate completion time for each process
    completionTime[0] = processes[0].burstTime;
    for (int i = 1; i < n; i++) {
        completionTime[i] = completionTime[i - 1] + processes[i].burstTime;
    }

    // Calculate turnaround time and waiting time for each process
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = completionTime[i] - processes[i].arrivalTime;
        waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
    }

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].processID);
    }
    printf("|\n");

    // Print processes details
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID,
               processes[i].arrivalTime, processes[i].burstTime,
               completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    // Calculate and print average turnaround time and average waiting time
    float avgTurnaroundTime = 0, avgWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        avgTurnaroundTime += turnaroundTime[i];
        avgWaitingTime += waitingTime[i];
    }
    avgTurnaroundTime /= n;
    avgWaitingTime /= n;

    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details from the user
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].processID = i + 1;
    }

    // Perform FCFS scheduling
    FCFS(processes, n);

    return 0;
}
