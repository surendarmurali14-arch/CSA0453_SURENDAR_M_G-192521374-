#include <stdio.h>

int main() {
    int n, i, j;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burstTime[n], waitingTime[n], turnaroundTime[n], process[n];

    // Input burst times
    for(i = 0; i < n; i++) {
        process[i] = i + 1;
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    // Sort processes based on burst time (SJF)
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(burstTime[i] > burstTime[j]) {
                // Swap burst times
                int temp = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = temp;

                // Swap process IDs
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    // Calculate Waiting Time
    waitingTime[0] = 0;
    for(i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }

    // Calculate Turnaround Time
    for(i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }

    // Display Results
    float totalWT = 0, totalTAT = 0;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n",
               process[i], burstTime[i], waitingTime[i], turnaroundTime[i]);

        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}