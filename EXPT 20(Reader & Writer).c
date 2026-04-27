#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared resources
sem_t mutex, writeBlock;
int data = 0;
int readersCount = 0;

void *reader(void *arg) {
    int f = *((int *)arg);
    for(int i = 0; i < 3; i++) {
        // Entry Section
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeBlock); // First reader blocks the writer
        }
        sem_post(&mutex);

        // Reading Operation
        printf("Reader %d reads data: %d\n", f, data);
        sleep(1); // Simulate time spent reading

        // Exit Section
        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock); // Last reader wakes up the writer
        }
        sem_post(&mutex);
        sleep(1);
    }
    return NULL;
}

void *writer(void *arg) {
    int f = *((int *)arg);
    for(int i = 0; i < 3; i++) {
        // Entry Section
        sem_wait(&writeBlock); // Writer gets exclusive access

        // Writing Operation
        data++;
        printf("Writer %d writes data: %d\n", f, data);
        sleep(1); // Simulate time spent writing

        // Exit Section
        sem_post(&writeBlock);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int ids[3] = {1, 2, 3};

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    // Creating 3 Reader threads and 2 Writer threads
    for(int i = 0; i < 3; i++) pthread_create(&r[i], NULL, reader, &ids[i]);
    for(int i = 0; i < 2; i++) pthread_create(&w[i], NULL, writer, &ids[i]);

    for(int i = 0; i < 3; i++) pthread_join(r[i], NULL);
    for(int i = 0; i < 2; i++) pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}