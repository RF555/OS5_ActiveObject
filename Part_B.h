#ifndef PART_B_H
#define PART_B_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Node structure for the queue
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// Thread-safe queue structure
typedef struct SafeQueue {
    Node *head;
    Node *tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} SafeQueue;


void initQueue(SafeQueue *queue);

void enqueue(SafeQueue *queue, void *data);

void *dequeue(SafeQueue *queue);

void freeQueue(SafeQueue *queue);


#endif
