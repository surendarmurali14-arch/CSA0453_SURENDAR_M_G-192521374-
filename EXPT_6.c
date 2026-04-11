#include <stdio.h>

int main() {
    int n, timeQuantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burstTime[n], remainingTime[n], waitingTime[n], turnaroundTime[n];
    int i, time = 0, done;
    
    // Input burst times
    for(i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        remainingTime[i] = burstTime[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    // Initialize waiting time
    for(i = 0; i < n; i++) {
        waitingTime[i] = 0;
    }

    // Round Robin Scheduling
    do {
        done = 1;
        for(i = 0; i < n; i++) {
            if(remainingTime[i] > 0) {
                done = 0;

                if(remainingTime[i] > timeQuantum) {
                    time += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    time += remainingTime[i];
                    waitingTime[i] = time - burstTime[i];
                    remainingTime[i] = 0;
                }
            }
        }
    } while(!done);

    // Calculate Turnaround Time
    for(i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }

    // Display Results
    float totalWT = 0, totalTAT = 0;
    
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i+1, burstTime[i], waitingTime[i], turnaroundTime[i]);
        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}