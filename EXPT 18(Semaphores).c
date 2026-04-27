#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep()

#define BUFFER_SIZE 5
#define MAX_ITEMS 10 

int buffer[BUFFER_SIZE];
sem_t empty, full;
int produced_items = 0, consumed_items = 0;

void* producer(void* arg) {
    while (produced_items < MAX_ITEMS) {
        sem_wait(&empty); // Wait if buffer is full

        // Critical section: add item to buffer
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] == 0) {
                buffer[i] = produced_items + 1;
                printf("Produced: %d\n", buffer[i]);
                produced_items++;
                break;
            }
        }

        sem_post(&full); // Signal that buffer has a new item
        sleep(1); 
    }
    return NULL;
}

void* consumer(void* arg) {
    while (consumed_items < MAX_ITEMS) {
        sem_wait(&full); // Wait if buffer is empty

        // Critical section: remove item from buffer
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            if (buffer[i] != 0) {
                printf("Consumed: %d\n", buffer[i]);
                buffer[i] = 0;
                consumed_items++;
                break;
            }
        }

        sem_post(&empty); // Signal that a slot is now free
        sleep(2); 
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initial empty slots: 5
    sem_init(&full, 0, 0);            // Initial full slots: 0

    // Create threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Join threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}