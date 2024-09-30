//Optimal Page Replacement Algorithm
#include <stdio.h>
#include <stdbool.h>

// Function to find the index of the page that will not be used for the longest period
int findOptimal(int pages[], int n, int frame[], int current, int capacity) {
    int res = -1, farthest = current;
    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = current; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

// Function to simulate OPT page replacement algorithm
void optimalPageReplace(int pages[], int n, int capacity) {
    int frame[capacity];
    bool isInMemory[capacity];
    int page_faults = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
        isInMemory[i] = false;
    }

    for (int i = 0; i < n; i++) {
        bool page_found = false;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                page_found = true;
                isInMemory[j] = true;
                break;
            }
        }

        if (!page_found) {
            int page_to_replace = findOptimal(pages, n, frame, i + 1, capacity);
            frame[page_to_replace] = pages[i];
            page_faults++;
        }

        // Print the page scheduling after each reference
        printf("Page %d: ", i + 1);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int n = 16;  // number of page references
    int pages[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int capacity = 3;  // number of memory frames

    optimalPageReplace(pages, n, capacity);

    return 0;
}
