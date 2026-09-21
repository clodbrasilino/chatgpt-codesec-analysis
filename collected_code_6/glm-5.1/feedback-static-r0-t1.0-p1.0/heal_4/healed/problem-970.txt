#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_minimum(int a, int b) {
    return a < b ? a : b;
}

int main(int argc, char * const * argv) {
    long val;
    int a, b;
    char *endptr;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    a = (int)val;

    errno = 0;
    val = strtol(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    b = (int)val;

    printf("%d\n", find_minimum(a, b));

    return EXIT_SUCCESS;
}