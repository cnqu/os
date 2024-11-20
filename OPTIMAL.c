

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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


 printf("Optimal Page Faults: %d\n", optimalPageFaults(referenceString, n, capacity));
    
    free(referenceString);
    return 0;
}
