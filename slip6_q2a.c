#include <stdio.h>

int main() {
    int referenceString[] = {0, 2, 1, 6, 4, 0, 1, 0, 3, 1, 2, 1};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    // Accept user input for the number of frames
    int MAX_FRAMES;
    printf("Enter the number of frames: ");
    scanf("%d", &MAX_FRAMES);

    int memoryFrames[MAX_FRAMES];
    int pageFaults = 0;
    int nextFrame = 0;
    int i, j;

    for (i = 0; i < MAX_FRAMES; i++) {
        memoryFrames[i] = -1;
    }

    for (i = 0; i < n; i++) {
        int page = referenceString[i];
        int found = 0;

        for (j = 0; j < MAX_FRAMES; j++) {
            if (memoryFrames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            memoryFrames[nextFrame] = page;
            nextFrame = (nextFrame + 1) % MAX_FRAMES;
            pageFaults++;
        }

        printf("Memory Frames: ");
        for (j = 0; j < MAX_FRAMES; j++) {
            if (memoryFrames[j] == -1) {
                printf("- ");
            } else {
                printf("%d ", memoryFrames[j]);
            }
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}
