#include "Part_C.h"

// Creates a new active object and starts its thread
ActiveObject *createActiveObject(int (*func)(void *)) {
    ActiveObject *ao = (ActiveObject *) malloc(sizeof(ActiveObject));
    ao->func = func;
    ao->queue = NULL;
    initQueue(ao->queue);
    pthread_create(&ao->thread, NULL, activeObjectThread, ao); // Creates thread and do the function
    return ao;
}

/* This function is called by the thread,
   it will dequeue the queue and execute the function passed in the active object */
void *activeObjectThread(ActiveObject *ao) {
    if (ao == NULL) return NULL; // If active object is null, return
    void *task = dequeue(ao->queue);
    while (task != NULL) { // While the queue is not empty
        ao->func(task);
        task = dequeue(ao->queue);
    }
}

SafeQueue *GetQueue(ActiveObject *ao) {
    return ao->queue;
}

void stop(ActiveObject *ao) {
    pthread_exit(&ao->thread);
    free(ao->queue);
    free(ao);
}