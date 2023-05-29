#include "Part_B.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Initialize the queue
void initQueue(SafeQueue *queue) {
    queue->head = NULL;
    queue->tail = NULL;
    pthread_mutex_init(&queue->mutex, NULL); // Initialize the mutex
    pthread_cond_init(&queue->cond, NULL); // Initialize the condition variable
}

// Enqueue an element in the queue
void enqueue(SafeQueue *queue, void *data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    pthread_mutex_lock(&queue->mutex); // Acquire the mutex lock

    if (queue->tail == NULL) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    pthread_cond_signal(&queue->cond); // Signal waiting threads

    pthread_mutex_unlock(&queue->mutex); // Release the mutex lock
}

// Dequeue an element from the queue
void *dequeue(SafeQueue *queue) {
    pthread_mutex_lock(&queue->mutex); // Acquire the mutex lock

    while (queue->head == NULL) {
        pthread_cond_wait(&queue->cond, &queue->mutex); // Wait until the queue is not empty
    }

    Node *node = queue->head;
    void *data = node->data;
    queue->head = node->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(node);

    pthread_mutex_unlock(&queue->mutex); // Release the mutex lock

    return data;
}

// Example usage
void *producer(void *arg) {
    SafeQueue *queue = (SafeQueue *) arg;

    for (int i = 0; i < 10; i++) {
        int *data = malloc(sizeof(int));
        *data = i;
        enqueue(queue, data);
    }

    return NULL;
}

void *consumer(void *arg) {
    SafeQueue *queue = (SafeQueue *) arg;

    for (int i = 0; i < 10; i++) {
        int *data = (int *) dequeue(queue);
        printf("Dequeued: %d\n", *data);
        free(data);
    }

    return NULL;
}

int main() {
    SafeQueue queue;
    initQueue(&queue);

    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, &queue);
    pthread_create(&consumerThread, NULL, consumer, &queue);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    return 0;
}