#include <stdio.h>

struct process {
    int pid; 
    int btime; 
    int pri; 
    int wtime; 
    int ttime;
    int atime;
} p[10], temp;

int main() {
    int i, j, k, n, ttur, twat;
    float awat, atur;

    printf("Enter no. of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Burst time for process P%d (in ms): ", (i + 1));
        scanf("%d", &p[i].btime);
        printf("Priority for process P%d: ", (i + 1));
        scanf("%d", &p[i].pri);
        printf("Arrival time for process P%d: ", (i + 1));
        scanf("%d", &p[i].atime);
        p[i].pid = i + 1;
    }

    // Sort the processes based on arrival time and priority
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if ((p[i].atime == 0 && p[j].atime != 0) ||
                (p[i].atime == 0 && p[j].atime == 0 && p[i].pri > p[j].pri) ||
                (p[i].atime == 0 && p[j].atime == 0 && p[i].pri == p[j].pri && p[i].pid > p[j].pid) ||
                (p[i].atime > 0 && p[j].atime > 0 && p[i].atime <= p[j].atime)) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].wtime = 0;

    for (i = 0; i < n; i++) {
        p[i + 1].wtime = p[i].wtime + p[i].btime;
        p[i].ttime = p[i].wtime + p[i].btime;
    }

    ttur = twat = 0;

    for (i = 0; i < n; i++) {
        ttur += p[i].ttime;
        twat += p[i].wtime;
    }

    awat = (float)twat / n;
    atur = (float)ttur / n;

    printf("\n\t Priority Scheduling\n\n");
    
    for (i = 0; i < 55; i++)
        printf("-");
    printf("\nProcess B-Time Priority Arrival T-Time  W-Time\n");
    
    for (i = 0; i < 55; i++)
        printf("-");
    
    for (i = 0; i < n; i++)
        printf("\n  P%-4d\t%4d\t%3d\t%4d\t%4d\t%4d",
            p[i].pid, p[i].btime, p[i].pri, p[i].atime, p[i].ttime, p[i].wtime);

    printf("\n");

    for (i = 0; i < 55; i++)
        printf("-");
    printf("\n\nGANTT Chart\n");
    printf("-");

    for (i = 0; i < (p[n - 1].ttime + 2 * n); i++)
        printf("-");
    printf("\n|");

    for (i = 0; i < n; i++) {
        k = p[i].btime / 2;
        for (j = 0; j < k; j++)
            printf(" ");
        printf("P%d", p[i].pid);
        for (j = k + 1; j < p[i].btime; j++)
            printf(" ");
        printf("|");
    }

    printf("\n-");

    for (i = 0; i < (p[n - 1].ttime + 2 * n); i++)
        printf("-");
    printf("\n0");

    for (i = 0; i < n; i++) {
        for (j = 0; j < p[i].btime; j++)
            printf(" ");
        printf("%2d", p[i].ttime);
    }

    printf("\n\nAverage waiting time     : %5.2fms", awat);
    printf("\nAverage turn around time : %5.2fms\n", atur);

    return 0;
}
