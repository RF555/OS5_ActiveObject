#ifndef PART_C_H
#define PART_C_H

#include "Part_B.h"

typedef struct ActiveObject {
    pthread_t thread;
    SafeQueue *queue;

    int (*func)(void *);
} ActiveObject, *PActiveObject;

ActiveObject *CreateActiveObject(int (*func)(void *));

SafeQueue *GetQueue(ActiveObject *ao);

void stop(ActiveObject *ao);

void *activeObjectThread(PActiveObject);


#endif
