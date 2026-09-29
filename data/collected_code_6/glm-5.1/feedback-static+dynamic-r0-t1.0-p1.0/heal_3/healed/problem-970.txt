#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int find_minimum(int a, int b) {
    return a < b ? a : b;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long long_a, long_b;
    char *endptr_a, *endptr_b;

    errno = 0;
    long_a = strtol(argv[1], &endptr_a, 10);
    if (errno != 0 || endptr_a == argv[1] || *endptr_a != '\0' || long_a < INT_MIN || long_a > INT_MAX) {
        return EXIT_FAILURE;
    }

    errno = 0;
    long_b = strtol(argv[2], &endptr_b, 10);
    if (errno != 0 || endptr_b == argv[2] || *endptr_b != '\0' || long_b < INT_MIN || long_b > INT_MAX) {
        return EXIT_FAILURE;
    }

    printf("%d\n", find_minimum((int)long_a, (int)long_b));

    return EXIT_SUCCESS;
}