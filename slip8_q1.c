#include <stdio.h>

void calculateNeedMatrix(int processes, int resources, int max_matrix[10][10], int alloc_matrix[10][10], int need_matrix[10][10]) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need_matrix[i][j] = max_matrix[i][j] - alloc_matrix[i][j];
        }
    }
}

void displayMatrix(int matrix[10][10], int rows, int cols) {
    printf("Need Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int processes, resources;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int max_matrix[10][10], alloc_matrix[10][10], need_matrix[10][10];

    // Input the maximum matrix
    printf("Enter the Maximum matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max_matrix[i][j]);
        }
    }

    // Input the allocation matrix
    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &alloc_matrix[i][j]);
        }
    }

    // Calculate and display the need matrix
    calculateNeedMatrix(processes, resources, max_matrix, alloc_matrix, need_matrix);
    displayMatrix(need_matrix, processes, resources);

    return 0;
}
