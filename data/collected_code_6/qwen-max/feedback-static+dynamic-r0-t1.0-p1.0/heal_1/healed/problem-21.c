#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void find_multiples(int n, int m) {
    for (int i = 1; i <= m; ++i) {
        printf("%d\n", n * i);
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long n = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || n < 1 || n > INT_MAX) {
        fprintf(stderr, "Invalid value for n. Must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    long m = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || m < 1 || m > INT_MAX) {
        fprintf(stderr, "Invalid value for m. Must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    find_multiples((int)n, (int)m);

    return EXIT_SUCCESS;
}