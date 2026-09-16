#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min(int a, int b, int c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <int1> <int2> <int3>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2, *endptr3;

    long val1 = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
        return EXIT_FAILURE;
    }

    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }

    long val3 = strtol(argv[3], &endptr3, 10);
    if (*endptr3 != '\0' || val3 < INT_MIN || val3 > INT_MAX) {
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;
    int c = (int)val3;

    int result = find_min(a, b, c);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}