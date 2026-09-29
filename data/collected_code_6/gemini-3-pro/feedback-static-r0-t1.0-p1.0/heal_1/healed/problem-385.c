#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long perrin(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 2;
    }
    return perrin(n - 2) + perrin(n - 3);
}

int main(int argc, const char * const argv[]) {
    long val;
    int n;
    char *endptr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer input.\n");
        return EXIT_FAILURE;
    }

    if (val < 0) {
        fprintf(stderr, "Error: n must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    if (val > 50) {
        fprintf(stderr, "Error: n is too large, it may cause performance issues or integer overflow.\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    unsigned long long result = perrin(n);
    printf("The %d'th Perrin number is %llu\n", n, result);

    return EXIT_SUCCESS;
}