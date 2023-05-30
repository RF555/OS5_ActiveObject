#ifndef PART_B_H
#define PART_B_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_QUEUE_SIZE 20

// Thread-safe queue structure
typedef struct SafeQueue {
    void *data[MAX_QUEUE_SIZE];
    int head;
    int tail;
    int size;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} SafeQueue;


/**
 * @brief Initialize the SafeQueue.
 * @param queue Pointer to a SafeQueue.
 */
void initQueue(SafeQueue *queue);

/**
 * @brief Add object to the queue.
 * @param queue Pointer to a SafeQueue.
 * @param data Object to add to the queue.
 */
void enqueue(SafeQueue *queue, void *data);

/**
 * @brief Get and remove the first object of the queue.
 * @param queue Pointer to a SafeQueue.
 * @return Pointer to the first object in the queue.
 */
void *dequeue(SafeQueue *queue);

//void freeQueue(SafeQueue *queue);


#endif
