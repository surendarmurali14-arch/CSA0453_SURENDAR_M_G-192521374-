#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Global matrices
int available[MAX_RESOURCES] = {3, 3, 2};
int maximum[MAX_PROCESSES][MAX_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int is_safe();

int request_resources(int process_num, int request[]) {
    // 1. Check if request <= need (maximum - allocation)
    // and if request <= available
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > (maximum[process_num][i] - allocation[process_num][i]) || 
            request[i] > available[i]) {
            return 0; // Request denied
        }
    }

    // 2. Temporarily allocate resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process_num][i] += request[i];
        maximum[process_num][i] -= request[i];
    }

    // 3. Check if system is in a safe state
    if (is_safe()) {
        return 1; // Request granted
    } else {
        // 4. Roll back changes if not safe
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process_num][i] -= request[i];
            maximum[process_num][i] += request[i];
        }
        return 0; // Request denied
    }
}

int is_safe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};

    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < MAX_PROCESSES) {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++) {
                    // Check if Need <= Work
                    if ((maximum[i][j] - allocation[i][j]) > work[j]) {
                        break;
                    }
                }
                
                if (j == MAX_RESOURCES) {
                    // Process can finish, update work
                    for (int k = 0; k < MAX_RESOURCES; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (found == 0) {
            return 0; // Not a safe state
        }
    }
    return 1; // Safe state
}

int main() {
    int process_num, request[MAX_RESOURCES];

    printf("Enter process number (0 to 4): ");
    scanf("%d", &process_num);
    
    printf("Enter resource request (e.g., 1 0 0): ");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }

    if (request_resources(process_num, request)) {
        printf("Request granted. System remains in a safe state.\n");
    } else {
        printf("Request denied. System would enter an unsafe state.\n");
    }

    return 0;
}