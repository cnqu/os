#include <stdio.h>

// Structure to represent a process
typedef struct {
    int pid;          // Process ID
    int arrivalTime;  // Arrival Time
    int burstTime;    // CPU Burst Time
    int completionTime; // Completion Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;   // Waiting Time
} Process;

void calculateFCFS(Process p[], int n) {
    // Variables to track time
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Compute completion time
        if (currentTime < p[i].arrivalTime)
            currentTime = p[i].arrivalTime;
        
        p[i].completionTime = currentTime + p[i].burstTime;

        // Update current time
        currentTime = p[i].completionTime;

        // Calculate TAT and WT
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
    }
}

void printResults(Process p[], int n) {
    printf("\nFCFS Scheduling Results:\n");
    printf("%-10s%-15s%-15s%-15s%-15s%-15s\n", 
           "PID", "Arrival", "Burst", "Completion", "TAT", "WT");

    for (int i = 0; i < n; i++) {
        printf("%-10d%-15d%-15d%-15d%-15d%-15d\n", 
               p[i].pid, 
               p[i].arrivalTime, 
               p[i].burstTime, 
               p[i].completionTime, 
               p[i].turnaroundTime, 
               p[i].waitingTime);
    }
}

int main() {
    int n;

    printf("Enter the number of p: ");
    scanf("%d", &n);

    Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    }

    // Sort p by Arrival Time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate times using FCFS
    calculateFCFS(p, n);

    // Print results
    printResults(p, n);

    return 0;
}
