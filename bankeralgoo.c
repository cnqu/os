#include <stdio.h>

int main() {
    int n, m;

    // Input the number of processes and resource types
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    int max[n][m], allocation[n][m], need[n][m], available[m];
    int finish[n], safeSeq[n];

    // Input maximum resource instances for each resource type
    printf("Enter the maximum resource instances for each resource type:\n");
    for (int i = 0; i < m; i++) {
        printf("Resource type %d: ", i);    
        scanf("%d", &available[i]);
    }

    // Input maximum resource allocation for each process
    printf("Enter the maximum resource allocation for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
        finish[i] = 0;  // Initialize all processes as unfinished
    }

    // Input current resource allocation for each process
    printf("Enter the current resource allocation for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            available[j] -= allocation[i][j];  // Update available resources
        }
    }

    // Calculate the need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Banker's Algorithm (finding the safe sequence)
    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {  // Process not yet finished
                int j;
                // Check if the process's needs can be satisfied
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        break;  // Cannot be satisfied, break the loop
                    }
                }
                // If all needs can be satisfied
                if (j == m) {
                    // Allocate resources to process i
                    for (int k = 0; k < m; k++) {
                        available[k] += allocation[i][k];  // Update available resources
                    }
                    safeSeq[count++] = i;  // Add process to safe sequence
                    finish[i] = 1;  // Mark process as finished
                    found = 1;  // Indicate that a process was found
                }
            }
        }
        // If no process could be found, system is not in a safe state
        if (!found) {
            printf("System is NOT in a safe state.\n");
            return 1;  // Exit with an error code
        }
    }

    // If all processes are in the safe sequence, print the output
    printf("System is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < n - 1; i++) {
        printf("P%d -> ", safeSeq[i]);
    }
    printf("P%d\n", safeSeq[n - 1]);

    return 0;
}
