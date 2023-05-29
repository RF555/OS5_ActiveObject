#include "Part_B.h"

// Example usage
void *producer(void *arg) {
    printf("Called producer()\n");
    SafeQueue *queue = (SafeQueue *) arg;

    for (int i = 0; i < 10; i++) {
        int *data = malloc(sizeof(int));
        *data = i;
        enqueue(queue, data);
        printf("Enqueued: %d\n", *data);
    }

    return NULL;
}

void *consumer(void *arg) {
    printf("Called consumer()\n");
    SafeQueue *queue = (SafeQueue *) arg;

    for (int i = 0; i < 10; i++) {
        int *data = (int *) dequeue(queue);
        printf("Dequeued: %d\n", *data);
        free(data);
    }

    return NULL;
}

int main() {
    PSafeQueue queue = NULL;
    initQueue(queue);
    printf("initiated queue\n");

    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, &queue);
    printf("created producerThread\n");
    pthread_create(&consumerThread, NULL, consumer, &queue);
    printf("created consumerThread\n");

    pthread_join(producerThread, NULL);
    printf("joined producerThread\n");
    pthread_join(consumerThread, NULL);
    printf("joined consumerThread\n");

    return 0;
}