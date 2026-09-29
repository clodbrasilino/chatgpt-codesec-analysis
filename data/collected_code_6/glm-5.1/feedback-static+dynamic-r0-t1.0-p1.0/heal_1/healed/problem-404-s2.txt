#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_minimum(int a, int b) {
    return a < b ? a : b;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Integer overflow\n");
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;
    int result = find_minimum(a, b);

    printf("%d\n", result);
    return EXIT_SUCCESS;
}