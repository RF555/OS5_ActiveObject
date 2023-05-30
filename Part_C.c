#include "Part_C.h"

void CreateActiveObject(ActiveObject *ao, SafeQueue *queue, Task task) {
    ao->task = task;
    ao->queue = queue;
    ao->active = 1;
    pthread_create(&ao->thread, NULL, activeObjectThread, ao);
    pthread_detach(ao->thread);
}

SafeQueue *GetQueue(ActiveObject *ao) {
    return ao->queue;
}

void stop(ActiveObject *ao) {
    ao->active = 0;

    pthread_cond_broadcast(&ao->queue->cond);

    pthread_join(ao->thread, NULL);

    pthread_mutex_lock(&ao->queue->mutex);

    while (ao->queue->size > 0) {
        pthread_cond_wait(&ao->queue->cond, &ao->queue->mutex); // Wait until the queue is empty
    }

    pthread_mutex_unlock(&ao->queue->mutex);
}

void *activeObjectThread(void *arg) {
    ActiveObject *ao = (ActiveObject *) arg;

    while (1) {
        void *task = dequeue(ao->queue);
        if (task != NULL) {
            ao->task(task);
        } else {
            pthread_mutex_lock(&ao->queue->mutex);
            int stop = !(ao->active);
            pthread_mutex_unlock(&ao->queue->mutex);

            if (stop) {
                break;
            }
        }
    }
    pthread_exit(NULL);
}

