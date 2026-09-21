#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if ((long)a + (long)b <= c) {
        return 0;
    }
    if ((long)a + (long)c <= b) {
        return 0;
    }
    if ((long)b + (long)c <= a) {
        return 0;
    }
    return 1;
}

int main(int argc, char * const * const argv) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    char *endptr1, *endptr2, *endptr3;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno == ERANGE) {
        return EXIT_FAILURE;
    }
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno == ERANGE) {
        return EXIT_FAILURE;
    }
    errno = 0;
    long val3 = strtol(argv[3], &endptr3, 10);
    if (errno == ERANGE) {
        return EXIT_FAILURE;
    }
    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0') {
        return EXIT_FAILURE;
    }
    if (val1 <= 0 || val1 > INT_MAX || val2 <= 0 || val2 > INT_MAX || val3 <= 0 || val3 > INT_MAX) {
        return EXIT_FAILURE;
    }
    int a = (int)val1;
    int b = (int)val2;
    int c = (int)val3;
    int result = is_valid_triangle(a, b, c);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}