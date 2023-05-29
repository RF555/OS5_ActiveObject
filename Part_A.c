#include "Part_A.h"

unsigned int isPrime(unsigned int n) {
    if (n == 3) {
        return n;
    }

    if (n <= 1 || n % 2 == 0 || n % 3 == 0) {
        return 0;
    }

    unsigned int i = 5;
    for (; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }

    return n;
}
