#ifndef PART_D_H
#define PART_D_H

#include <unistd.h>
//#include <time.h>

#include "Part_A.h"
#include "Part_B.h"
#include "Part_C.h"

#define ERROR_PRINT "  \x1b[1;31m"
#define RESET_COLOR "\x1b[0m"


typedef struct {
    unsigned int number;
    int serial;
    /**
     * @brief 1 - prime\n
     * 0 - not prime
     */
    int is_prime;
    /**
     * @brief -1 - no seed\n
     * else - seed
     */
    int rand_seed;
    int nums;
} task_t;

/**
 * @brief Initialize random generator with given random seed.\n
 * @brief Generate a given number of 6 digits random numbers.
 * @brief Pass generated numbers one by one to the 2'nd AO.
 * @param task1 Pointer to a task_t.
 */
void AO_Task1(void *task1);

/**
 * @brief Print the given number.\n
 * @brief Check if the number is prime and print the result.
 * @brief Add 11 to the number and pass it to the 3'rd AO.
 * @param task2 Pointer to a task_t.
 */
void AO_Task2(void *task2);

/**
 * @brief Print the given number.\n
 * @brief Check if the number is prime and print the result.
 * @brief Subtract 13 from the number and pass it to the 4'th AO.
 * @param task3 Pointer to a task_t.
 */
void AO_Task3(void *task3);

/**
 * @brief Print the given number.\n
 * @brief Add 2 to the number and print the new number. (should be equal to the original number from 1'st AO).
 * @param task4 Pointer to a task_t.
 */
void AO_Task4(void *task4);

void setupPipeline(int _nums, int _rand_seed);

void stopPipeline();


#endif
