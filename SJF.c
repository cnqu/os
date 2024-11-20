#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;           // Process ID
    int arrivalTime;   // Arrival Time
    int burstTime;     // CPU Burst Time
    int remainingTime; // Remaining Time (for preemptive)
    int completionTime;// Completion Time
    int turnaroundTime;// Turnaround Time
    int waitingTime;   // Waiting Time
} Process;

// Function to calculate SJF Non-Preemptive
void sjfNonPreemptive(Process p[], int n) {
    int completed = 0, currentTime = 0;

    while (completed < n) {
        int minBurst = INT_MAX, idx = -1;

        // Find the process with the smallest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].completionTime == 0 && p[i].burstTime < minBurst) {
                minBurst = p[i].burstTime;
                idx = i;
            }
        }

        if (idx != -1) {
            currentTime += p[idx].burstTime;
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            completed++;
        } else {
            currentTime++;
        }
    }
}

// Function to calculate SJF Preemptive
void sjfPreemptive(Process p[], int n) {
    int completed = 0, currentTime = 0;

    while (completed < n) {
        int minRemaining = INT_MAX, idx = -1;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0 && p[i].remainingTime < minRemaining) {
                minRemaining = p[i].remainingTime;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].remainingTime--;
            currentTime++;

            // If the process finishes
            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
}

// Function to print the results
void printResults(Process p[], int n, const char *mode) {
    printf("\n%s SJF Scheduling Results:\n", mode);
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

    Process p[n], backup[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].completionTime = 0; // Initialize as not completed
        p[i].remainingTime = p[i].burstTime; // Initialize remaining time
        backup[i] = p[i]; // Backup for reuse
    }

    // SJF Non-Preemptive
    sjfNonPreemptive(p, n);
    printResults(p, n, "Non-Preemptive");

    // Restore backup for Preemptive
    for (int i = 0; i < n; i++) {
        p[i] = backup[i];
    }

    // SJF Preemptive
    sjfPreemptive(p, n);
    printResults(p, n, "Preemptive");
 

    return 0;
}
