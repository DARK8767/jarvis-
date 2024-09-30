#include <stdio.h>
#include <time.h>

int main() {
    // Record the start time
    clock_t start_time = clock();
    // For example, a loop that does some computations
    for (int i = 0; i < 10000; ++i) {
        // Some computation
        int result = i * i;
    }

    // Record the end time
    clock_t end_time = clock();

    // Calculate the execution time in seconds
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the execution time
    printf("Execution Time: %f seconds\n", execution_time);

    return 0;
}
