#include "Part_B.h"

void initializeQueue(SafeQueue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);
}

void enqueue(SafeQueue *queue, int item) {
    pthread_mutex_lock(&queue->mutex);

    // Wait until there is space in the queue
    while (queue->count >= QUEUE_SIZE) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    queue->rear = (queue->rear + 1) % QUEUE_SIZE;
    queue->data[queue->rear] = item;
    queue->count++;

    // Signal that an item has been added to the queue
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
}

int dequeue(SafeQueue *queue) {
    pthread_mutex_lock(&queue->mutex);

    // Wait until there is an item in the queue
    while (queue->count == 0) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    int item = queue->data[queue->front];
    queue->front = (queue->front + 1) % QUEUE_SIZE;
    queue->count--;

    // Signal that an item has been removed from the queue
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);

    return item;
}

int main() {
    SafeQueue queue;
    initializeQueue(&queue);

    // Create threads for enqueue and dequeue operations
    pthread_t enqueueThread, dequeueThread;
    pthread_create(&enqueueThread, NULL, (void *) enqueue, &queue);
    pthread_create(&dequeueThread, NULL, (void *) dequeue, &queue);

    // Wait for the threads to finish
    pthread_join(enqueueThread, NULL);
    pthread_join(dequeueThread, NULL);

    // Cleanup
    pthread_mutex_destroy(&queue.mutex);
    pthread_cond_destroy(&queue.cond);

    return 0;
}
