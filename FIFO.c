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
    printf("FIFO Page Faults: %d\n", fifoPageFaults(referenceString, n, capacity));

   

    free(referenceString);
    return 0;
}
