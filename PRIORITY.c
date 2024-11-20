#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;           // Process ID
    int arrivalTime;   // Arrival Time
    int burstTime;     // CPU Burst Time
    int priority;      // Priority
    int remainingTime; // Remaining Time (for preemptive)
    int completionTime;// Completion Time
    int turnaroundTime;// Turnaround Time
    int waitingTime;   // Waiting Time
} Process;

// Function to calculate Priority Non-Preemptive
void priorityNonPreemptive(Process processes[], int n) {
    int completed = 0, currentTime = 0;

    while (completed < n) {
        int highestPriority = INT_MAX, idx = -1;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].completionTime == 0 && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            currentTime += processes[idx].burstTime;
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            completed++;
        } else {
            currentTime++;
        }
    }
}

// Function to calculate Priority Preemptive
void priorityPreemptive(Process processes[], int n) {
    int completed = 0, currentTime = 0;

    while (completed < n) {
        int highestPriority = INT_MAX, idx = -1;

        // Find the process with the highest priority and shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            processes[idx].remainingTime--;
            currentTime++;

            // If the process finishes
            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
}

// Function to print the results
void printResults(Process processes[], int n, const char *mode) {
    printf("\n%s Priority Scheduling Results:\n", mode);
    printf("%-10s%-15s%-15s%-15s%-15s%-15s%-15s\n", 
           "PID", "Arrival", "Burst", "Priority", "Completion", "TAT", "WT");

    for (int i = 0; i < n; i++) {
        printf("%-10d%-15d%-15d%-15d%-15d%-15d%-15d\n", 
               processes[i].pid, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].priority, 
               processes[i].completionTime, 
               processes[i].turnaroundTime, 
               processes[i].waitingTime);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n], backup[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", processes[i].pid);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].completionTime = 0; // Initialize as not completed
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
        backup[i] = processes[i]; // Backup for reuse
    }

    // Priority Non-Preemptive
    priorityNonPreemptive(processes, n);
    printResults(processes, n, "Non-Preemptive");

    // Restore backup for Preemptive
    for (int i = 0; i < n; i++) {
        processes[i] = backup[i];
    }

    // Priority Preemptive
    priorityPreemptive(processes, n);
    printResults(processes, n, "Preemptive");

    return 0;
}
