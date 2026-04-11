#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

int main() {
    key_t key = 1234;

    // Create shared memory
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Attach shared memory
    char *str = (char*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) {
        // Child Process (Reader)
        sleep(1);  // wait for parent to write
        printf("Child reads: %s\n", str);
    } else {
        // Parent Process (Writer)
        printf("Parent writing to shared memory...\n");
        strcpy(str, "Hello from Parent Process!");
        printf("Data written.\n");
    }

    return 0;
}