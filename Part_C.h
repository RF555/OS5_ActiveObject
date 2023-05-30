#ifndef PART_C_H
#define PART_C_H

#include "Part_B.h"

typedef void (*Task)(void *);

typedef struct ActiveObject {
    pthread_t thread;
    SafeQueue *queue;
    Task task;
    /**
     * @brief 1 - active\n
     * 0 - dead
     */
    int active;
} ActiveObject;

/**
 * @brief Creates and allocate new ActiveObject on a new thread.
 * @param ao Pointer to an ActiveObject.
 * @param queue Pointer to a SafeQueue.
 * @param task Task needed to execute.
 */
void CreateActiveObject(ActiveObject *ao, SafeQueue *queue, Task task);

/**
 * @brief Get the ActiveObject's SafeQueue.
 * @param ao Pointer to an ActiveObject.
 * @return Pointer to the ActiveObject's queue.
 */
SafeQueue *GetQueue(ActiveObject *ao);

/**
 * @brief Stops the ActiveObject.\n If the task is yet to finish - wait for it to finish.
 * @param ao Pointer to an ActiveObject.
 */
void stop(ActiveObject *ao);

/**
 * @brief The ActiveObject's thread function.
 * @return ActiveObject.
 */
void *activeObjectThread(void *arg);


#endif
