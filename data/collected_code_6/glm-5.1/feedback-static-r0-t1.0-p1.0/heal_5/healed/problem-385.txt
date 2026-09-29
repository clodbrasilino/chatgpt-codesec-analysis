#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int perrin(int n) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    } else if (n == 1) {
        return 3;
    } else if (n == 2) {
        return 0;
    } else if (n == 3) {
        return 2;
    } else {
        return perrin(n - 2) + perrin(n - 3);
    }
}

int main(int argc, char * const argv[const]) {
    long n;
    char *endptr;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    n = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || n <= 0 || n > INT_MAX) {
        return EXIT_FAILURE;
    }
    printf("%d\n", perrin((int)n));
    return EXIT_SUCCESS;
}