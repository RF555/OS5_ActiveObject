#ifndef PART_B_H
#define PART_B_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define QUEUE_SIZE 1000

typedef struct {
    int data[QUEUE_SIZE];
    int front;
    int rear;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} SafeQueue;

void initializeQueue(SafeQueue *queue);

void enqueue(SafeQueue *queue, int item);

int dequeue(SafeQueue *queue);

#endif
