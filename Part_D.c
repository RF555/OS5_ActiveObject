#include "Part_D.h"

ActiveObject ao1, ao2, ao3, ao4;
SafeQueue queue1, queue2, queue3, queue4;

void AO_Task1(void *task1) {
    printf("Called AO_Task1()\n");
    task_t *task = (task_t *) task1;
    static int init = 0;
    if (!init) {
        if (task->rand_seed == -1) {
            srand(time(NULL));
        } else {
            srand(task->rand_seed);
        }
        init = 1;
    }
    for (int i = 0; i < task->nums; ++i) {
        task_t *new_task = malloc(sizeof(task_t));
        *new_task = *task;
        new_task->number = (rand() % 900000) + 100000;
        new_task->serial = i + 1;
        printf("%d number: %d\n", new_task->serial, new_task->number);
        struct timespec remaining, request = {0, 1000};
        nanosleep(&request, &remaining);
        enqueue(&queue2, new_task);
    }
    free(task);
}

void AO_Task2(void *task2) {
    printf("Called AO_Task2()\n");
    task_t *task = (task_t *) task2;
    printf("%d number: %d\n", task->serial, task->number);
    printf("Is %d prime: %s\n", task->number, isPrime(task->number) ? "True" : "False");
    task->number += 11;
    enqueue(&queue3, task);
}

void AO_Task3(void *task3) {
    printf("Called AO_Task3()\n");
    task_t *task = (task_t *) task3;
    printf("%d number: %d\n", task->serial, task->number);
    printf("Is %d prime: %s\n", task->number, isPrime(task->number) ? "True" : "False");
    task->number -= 13;
    enqueue(&queue4, task);
}

void AO_Task4(void *task4) {
    printf("Called AO_Task4()\n");
    task_t *task = (task_t *) task4;
    printf("%d number: %d\n", task->serial, task->number);
    task->number += 2;
    printf("new %d number: %d\n", task->serial, task->number);
}

void setupPipeline(int _nums, int _rand_seed) {
    initQueue(&queue1);
    initQueue(&queue2);
    initQueue(&queue3);
    initQueue(&queue4);

    CreateActiveObject(&ao1, &queue1, AO_Task1);
    CreateActiveObject(&ao2, &queue2, AO_Task2);
    CreateActiveObject(&ao3, &queue3, AO_Task3);
    CreateActiveObject(&ao4, &queue4, AO_Task4);

    task_t *task = NULL;
    if ((task = (task_t *) malloc(sizeof(task_t))) == NULL) {
        fprintf(stderr, "%smalloc() failed.%s\n", ERROR_PRINT, RESET_COLOR);
        return;
    }
    task->rand_seed = _rand_seed;
    task->nums = _nums;
    enqueue(&queue1, task);
}

void stopPipeline() {
    while (queue1.size > 0 || queue2.size > 0 || queue3.size > 0 || queue4.size > 0) {
        sleep(1);
    }
    stop(&ao1);
    stop(&ao2);
    stop(&ao3);
    stop(&ao4);
}

