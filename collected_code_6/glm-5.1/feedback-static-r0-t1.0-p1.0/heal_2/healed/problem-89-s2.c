#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int closest_smaller(int n) {
    if (n <= 1) {
        return -1;
    }
    return n - 1;
}

int main(int argc, char const * const argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    int result = closest_smaller(n);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}