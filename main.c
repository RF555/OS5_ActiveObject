#include "Part_B.h"

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
