#include "Part_D.h"

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: %s N [seed]\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int seed = (argc == 3) ? atoi(argv[2]) : -1;

    setupPipeline(N, seed);

    stopPipeline();


    return 0;
}


