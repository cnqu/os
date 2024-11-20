#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;           // Process ID
    int arrivalTime;   // Arrival Time
    int burstTime;     // Burst Time
    int remainingTime; // Remaining Time
    int completionTime;// Completion Time
    int turnaroundTime;// Turnaround Time
    int waitingTime;   // Waiting Time
} Process;

void roundRobinScheduling(Process processes[], int n, int timeQuantum) {
    int currentTime = 0, completed = 0;
    bool done;
    
    while (completed < n) {
        done = true;

        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                done = false;

                // Check if the process is ready to execute
                if (processes[i].arrivalTime <= currentTime) {
                    if (processes[i].remainingTime <= timeQuantum) {
                        currentTime += processes[i].remainingTime;
                        processes[i].remainingTime = 0;
                        processes[i].completionTime = currentTime;
                        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                        completed++;
                    } else {
                        currentTime += timeQuantum;
                        processes[i].remainingTime -= timeQuantum;
                    }
                } else {
                    currentTime++;
                }
            }
        }

        if (done) break;
    }
}

// Function to display the results
void printResults(Process processes[], int n) {
    printf("\nRound Robin Scheduling Results:\n");
    printf("%-10s%-15s%-15s%-15s%-15s%-15s\n", 
           "PID", "Arrival", "Burst", "Completion", "TAT", "WT");
    
    for (int i = 0; i < n; i++) {
        printf("%-10d%-15d%-15d%-15d%-15d%-15d\n", 
               processes[i].pid, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].completionTime, 
               processes[i].turnaroundTime, 
               processes[i].waitingTime);
    }
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
    }

    // Input the time quantum
    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    // Perform Round Robin Scheduling
    roundRobinScheduling(processes, n, timeQuantum);

    // Print results
    printResults(processes, n);

    return 0;
}
