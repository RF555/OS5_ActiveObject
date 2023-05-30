#include "Part_B.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Initialize the queue
void initQueue(SafeQueue *queue) {
    queue->head = 0;
    queue->tail = -1;
    queue->size = 0;
    pthread_mutex_init(&queue->mutex, NULL); // Initialize the mutex
    pthread_cond_init(&queue->cond, NULL); // Initialize the condition variable
}

// Enqueue an element in the queue
void enqueue(SafeQueue *queue, void *data) {
    pthread_mutex_lock(&queue->mutex); // Acquire the mutex lock
    while (queue->size >= MAX_QUEUE_SIZE) { // Wait as long as the queue is full
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;
    queue->data[queue->tail] = data;
    queue->size++;

    pthread_cond_signal(&queue->cond); // Signal waiting threads

    pthread_mutex_unlock(&queue->mutex); // Release the mutex lock
}

// Dequeue an element from the queue
void *dequeue(SafeQueue *queue) {
    pthread_mutex_lock(&queue->mutex); // Acquire the mutex lock

    while (queue->size <= 0) {
        pthread_cond_wait(&queue->cond, &queue->mutex); // Wait until the queue is not empty
    }

    void *data = queue->data[queue->head];
    queue->head = (queue->head+1)&MAX_QUEUE_SIZE;
    queue->size--;

    pthread_cond_signal(&queue->cond); // Signal waiting threads

    pthread_mutex_unlock(&queue->mutex); // Release the mutex lock

    return data;
}

//void freeQueue(SafeQueue *queue) {
//    while (queue->head != NULL) {
//        Node *temp_node = queue->head;
//        queue->head = queue->head->next;
//        free(temp_node);
//    }
//    pthread_mutex_destroy(&queue->mutex);
//    pthread_cond_destroy(&queue->cond);
//    free(queue);
//}
