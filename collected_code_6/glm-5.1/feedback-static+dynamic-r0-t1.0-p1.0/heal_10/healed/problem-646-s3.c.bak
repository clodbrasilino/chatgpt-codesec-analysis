#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long count_cubes(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }

    unsigned long long diff = (unsigned long long)(n - k);
    unsigned long long cubes = (diff + 1) * (diff + 1) * (diff + 1);
    
    return cubes;
}

int main(int argc, char * const argv[const]) {
    int n = 0, k = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_n, *endptr_k;
    long val_n = strtol(argv[1], &endptr_n, 10);
    long val_k = strtol(argv[2], &endptr_k, 10);

    if (*endptr_n != '\0' || val_n < 0 || val_n > INT_MAX ||
        *endptr_k != '\0' || val_k < 0 || val_k > INT_MAX) {
        fprintf(stderr, "Error: n and k must be non-negative integers.\n");
        return EXIT_FAILURE;
    }

    n = (int)val_n;
    k = (int)val_k;

    unsigned long long result = count_cubes(n, k);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}