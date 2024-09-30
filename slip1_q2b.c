//Banker's Algorithm
#include <stdio.h>
void main() {
  int n, m, i, j, k;

  printf("Enter the number of processes: ");
  scanf("%d", &n);

  printf("Enter the number of resource types: ");
  scanf("%d", &m);

  int alloc[n][m];
  int max[n][m];
  int need[n][m];
  int avail[m];
  int request[m];

  // Input the allocation matrix
  printf("\nEnter the allocation matrix:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      scanf("%d", &alloc[i][j]);
    }
  }

  // Input the maximum demand matrix
  printf("\nEnter the maximum demand matrix:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      scanf("%d", &max[i][j]);
    }
  }

  // Calculate the need matrix
  printf("\nNeed Matrix:\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      need[i][j] = max[i][j] - alloc[i][j];
      printf("%d ", need[i][j]);
    }
    printf("\n");
  }

  // Input the available resources
  printf("\nEnter the available resources:\n");
  for (j = 0; j < m; j++) {
    scanf("%d", &avail[j]);
  }

  // Check for safe state
  int finish[n];
  int work[m];

  for (i = 0; i < m; i++) {
    work[i] = avail[i];
  }

  for (i = 0; i < n; i++) {
    finish[i] = 0;
  }

  int safe = 1;
  int count = 0;
  int safe_sequence[n];

  while (count < n && safe) {
    for (i = 0; i < n; i++) {
      if (finish[i] == 0) {
        int flag = 1;

        for (j = 0; j < m; j++) {
          if (need[i][j] > work[j]) {
            flag = 0;
            break;
          }
        }

        if (flag) {
          for (j = 0; j < m; j++) {
            work[j] += alloc[i][j];
          }

          finish[i] = 1;
          count++;
          safe_sequence[count - 1] = i;
        }
      }
    }
  }

  // Display safe sequence

  if (safe) {
    printf("\nThe system is in a safe state.\n");
    printf("\nSafe Sequence: ");
    for (i = 0; i < n; i++) {
      printf("%d ", safe_sequence[i]);
    }
  } else {
    printf("\nThe system is in an unsafe state.\n");
  }

  // Check if the request can be granted

  printf("\nEnter the request vector for process P: ");
  for (i = 0; i < m; i++) {
    scanf("%d", &request[i]);
  }

  int can_grant = 1;

  for (i = 0; i < m; i++) {
    if (request[i] > need[0][i]) {
      can_grant = 0;
      break;
    }
  }

  if (can_grant) {
    for (i = 0; i < m; i++) {
      need[0][i] -= request[i];
      avail[i] -= request[i];
    }

    printf("\nThe request can be granted immediately.\n");
  } else {
    printf("\nThe request cannot be granted immediately. \n");
  }
}
