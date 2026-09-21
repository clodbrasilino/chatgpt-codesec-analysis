#include <stdio.h>
#include <stdlib.h>

#define MAX_N 64

unsigned long perrin(int n) {
    if (n < 0) return 0;
    unsigned long p[MAX_N];
    p[0] = 3;
    p[1] = 0;
    p[2] = 2;
    if (n < 3) return p[n];
    for (int i = 3; i <= n; i++) {
        p[i] = p[i - 2] + p[i - 3];
    }
    return p[n];
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 0) {
        fprintf(stderr, "Error: n must be a non-negative integer\n");
        return EXIT_FAILURE;
    }

    if (val >= MAX_N) {
        fprintf(stderr, "Error: n exceeds maximum allowed value\n");
        return EXIT_FAILURE;
    }

    unsigned long result = perrin((int)val);
    printf("%lu\n", result);

    return EXIT_SUCCESS;
}