// Round Robin Algorithm
#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid; // Process ID
    int arrivalTime; // Arrival time of the process
    int burstTime; // Burst time of the process
    int remainingTime; // Remaining burst time of the process
    int waitingTime; // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
};

// Function to calculate waiting time, turnaround time, and generate Gantt chart
void roundRobinScheduling(struct Process processes[], int n, int timeQuantum) {
    int currentTime = 0; // Current time
    int completedProcesses = 0; // Number of completed processes

    // Loop until all processes are completed
    printf("---- GANTT CHART ----\n");
    while (completedProcesses < n) {
        // Traverse through all processes
        for (int i = 0; i < n; i++) {
            // Skip the process if it is already completed
            if (processes[i].remainingTime == 0) {
                continue;
            }

            // Execute the process for the time quantum or remaining burst time, whichever is smaller
            int executionTime = (processes[i].remainingTime < timeQuantum) ? processes[i].remainingTime : timeQuantum;

            // Update the remaining burst time of the process
            processes[i].remainingTime -= executionTime;

            // Update the current time
            currentTime += executionTime;

            // Generate Gantt chart
            printf("| P%d ", processes[i].pid);

            // Check if the process is completed
            if (processes[i].remainingTime == 0) {
                // Calculate waiting time and turnaround time
                processes[i].waitingTime = currentTime - processes[i].arrivalTime - processes[i].burstTime;
                processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;

                // Increment the number of completed processes
                completedProcesses++;
            }
        }
    }

    // Print the turnaround time and waiting time for each process
    printf("|\n\n");
    printf("Process\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d \t%d\t\t%d\n", processes[i].pid, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    // Calculate the average waiting time and turnaround time
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }
    float averageWaitingTime = (float)totalWaitingTime / n;
    float averageTurnaroundTime = (float)totalTurnaroundTime / n;

    // Print the average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}

int main() {
    int n; // Number of processes
    int timeQuantum; // Time quantum

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input the time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    // Declare an array of processes
    struct Process processes[n];

    // Input the arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process P%d: ", i);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].pid = i;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Call the roundRobinScheduling function
    roundRobinScheduling(processes, n, timeQuantum);

    return 0;
}
