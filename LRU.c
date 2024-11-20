

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



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


  printf("LRU Page Faults: %d\n", lruPageFaults(referenceString, n, capacity));
  

    free(referenceString);
    return 0;
}
