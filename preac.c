

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int fifoPageFaults(char* referenceString, int n, int capacity) {
    char* pageQueue = (char*)malloc(capacity * sizeof(char));
    int front = 0, rear = 0, size = 0;
    bool pageSet[256] = { false }; // Assume ASCII characters
    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        char page = referenceString[i];
        if (!pageSet[page]) {
            if (size == capacity) {
                char oldestPage = pageQueue[front];
                pageSet[oldestPage] = false;
                front = (front + 1) % capacity;
                size--;
            }
            pageQueue[rear] = page;
            rear = (rear + 1) % capacity;
            pageSet[page] = true;
            size++;
            pageFaults++;
        }
    }

    free(pageQueue);
    return pageFaults;
}

int lruPageFaults(char* referenceString, int n, int capacity) {
    char* pageList = (char*)malloc(capacity * sizeof(char));
    int* timeStamps = (int*)malloc(capacity * sizeof(int));
    int pageFaults = 0, size = 0;

    for (int i = 0; i < n; i++) {
        char page = referenceString[i];
        int found = -1;

        for (int j = 0; j < size; j++) {
            if (pageList[j] == page) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            timeStamps[found] = i;
        } else {
            if (size == capacity) {
                int lruIndex = 0;
                for (int j = 1; j < size; j++) {
                    if (timeStamps[j] < timeStamps[lruIndex]) {
                        lruIndex = j;
                    }
                }
                for (int j = lruIndex; j < size - 1; j++) {
                    pageList[j] = pageList[j + 1];
                    timeStamps[j] = timeStamps[j + 1];
                }
                size--;
            }
            pageList[size] = page;
            timeStamps[size] = i;
            size++;
            pageFaults++;
        }
    }

    free(pageList);
    free(timeStamps);
    return pageFaults;
}

int optimalPageFaults(char* referenceString, int n, int capacity) {
    char* pages = (char*)malloc(capacity * sizeof(char));
    int pageFaults = 0, size = 0;

    for (int i = 0; i < n; i++) {
        char page = referenceString[i];
        int found = -1;

        for (int j = 0; j < size; j++) {
            if (pages[j] == page) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            if (size == capacity) {
                int farthestIndex = -1, farthestPage = -1;

                for (int j = 0; j < size; j++) {
                    int nextIndex = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (pages[j] == referenceString[k]) {
                            nextIndex = k;
                            break;
                        }
                    }
                    if (nextIndex == -1 || nextIndex > farthestIndex) {
                        farthestIndex = nextIndex;
                        farthestPage = j;
                    }
                }
                for (int j = farthestPage; j < size - 1; j++) {
                    pages[j] = pages[j + 1];
                }
                size--;
            }
            pages[size] = page;
            size++;
            pageFaults++;
        }
    }

    free(pages);
    return pageFaults;
}

int main() {
    int capacity, n;

    printf("Enter the number of page frames: ");
    scanf("%d", &capacity);

    printf("Enter the size of reference string: ");
    scanf("%d", &n);

    char* referenceString = (char*)malloc(n * sizeof(char));
    printf("Enter the elements of reference string (separated by space): ");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &referenceString[i]);
    }

    int choice;
    do {
        printf("\nPage Replacement Algorithms Menu:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("FIFO Page Faults: %d\n", fifoPageFaults(referenceString, n, capacity));
                break;
            case 2:
                printf("LRU Page Faults: %d\n", lruPageFaults(referenceString, n, capacity));
                break;
            case 3:
                printf("Optimal Page Faults: %d\n", optimalPageFaults(referenceString, n, capacity));
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    free(referenceString);
    return 0;
}
